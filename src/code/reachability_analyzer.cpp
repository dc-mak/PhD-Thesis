// 1. The PreprocessingRecord only inlcudes the Macro expanded when typed into
//    the source, not any subsequent macros expanded _inside a macro_.
// 2. None of getFileLoc, getExpansionLoc, get(Immediate)SpellingLoc, in
//    SourceManager::() enable to go from the source _down_/expand the macros,
//    only to go from a fully expanded location back up to the source.
// 3. It seems difficult/not sensible to re-lex/pp the macro _definition_ to get
//    at the macros it refers to.
// Therefore, we add a PPCallback that records _all_ macro expansions, even
// those that occur within a macro.
void ReachabilityAnalyzer::ExecuteAction() {
    auto &ci = getCompilerInstance();
    auto &pp = ci.getPreprocessor();
    PPRecordNested::RangeToSet macro_deps;
    PPRecordNested::RangeToRange range_hack;
    const auto &sm = ci.getSourceManager();
    pp.addPPCallbacks(std::make_unique<PPRecordNested>(macro_deps, range_hack, sm));

    // this runs the pre-processor and declaration traversal & marking
    ASTFrontendAction::ExecuteAction();

    if (!kept_lines)
        CTC_DEBUG(std::cerr << "No preprocessing record found :(" << std::endl);

    // you need this for `PreprocessingRecord::getPreprocessedEntitiesInRange`
    auto *pr = pp.getPreprocessingRecord();
    if (!pr) {
        CTC_DEBUG(std::cerr << "No preprocessing record found :(" << std::endl);
        return;
    }

    // mark the marcros used inside all declaration ranges
    SourceRangeSet marked;
    for (const auto &range : m_ranges)
        findMacroDefns(*pr, sm, range, macro_deps, range_hack, marked);
}

void HandleTranslationUnit(clang::ASTContext &context) override {
    const auto &sm = context.getSourceManager();
    auto *const tu = context.getTranslationUnitDecl();
    auto &diagnostics = context.getDiagnostics();
    const auto not_after_id = diagnostics.getCustomDiagID(
        clang::DiagnosticsEngine::Error, "declaration '%1' must start on a line "
                                         "after the end of declaration '%0'");

    // CTC_DEBUG(tu->dump());

    if (!InputValidator{diagnostics, sm, not_after_id}.ToplevelOnDiffLines(tu))
        return;

    const auto roots = getFuncRoots(tu, context.Idents, sm);
    const auto transitive = Traverser{sm, roots}.get_traversed_decls();

    std::vector<const clang::Decl *> to_mark;
    std::copy_if(tu->decls_begin(), tu->decls_end(), std::back_inserter(to_mark),
                 [&transitive](const clang::Decl *decl) {
                     return (transitive.find(decl) != transitive.end() ||
                             isAFwdDeclWhoseDefIsTraversed(decl, transitive));
                 });
    kept_lines = SourceMarker{sm, transitive, to_mark, m_ranges}.get_kept_lines();
}
