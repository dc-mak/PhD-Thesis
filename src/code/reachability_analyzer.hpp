void MacroDefined(const clang::Token &Id, const clang::MacroDirective *MD) override {
    assert(MD);
    const auto *macro_info = MD->getMacroInfo();
    assert(macro_info);
    auto orig = clang::SourceRange(
        macro_info->getDefinitionLoc(),
        macro_info->getDefinitionEndLoc());
    // Multi-token macros need special handling, see original for gory details
    if (const auto num_tokens = macro_info->getNumTokens(); num_tokens > 0) {
        const auto &last_token =
            macro_info->getReplacementToken(macro_info->getNumTokens() - 1);
        m_range_hack[orig] = clang::SourceRange(
            orig.getBegin(),
            last_token.getLocation().getLocWithOffset(last_token.getLength() - 1));
    } else {
        m_range_hack[orig] = clang::SourceRange(
            orig.getBegin(), orig.getBegin().getLocWithOffset(Id.getLength() - 1));
    }
}

void MacroExpands(const clang::Token &Id, const clang::MacroDefinition &MD,
                  clang::SourceRange Range, const clang::MacroArgs *Args) override {
    static bool assigned = false;
    static clang::SourceRange outer_macro_defn_range;
    if (!Id.getLocation().isMacroID()) {
        outer_macro_defn_range = defn_range(MD);
        assigned = true;
        CTC_DEBUG(std::cerr << "TL Macro: " << Id.getIdentifierInfo()->getNameStart()
                            << std::endl);
    } else {
        assert(assigned);
        int count = 0;
        for (auto loc = Id.getLocation(); loc.isMacroID();
             loc = m_sm.getImmediateMacroCallerLoc(loc), count++) {
        }
        CTC_DEBUG(std::cerr << std::string(count * 2, ' ')
                            << Id.getIdentifierInfo()->getNameStart() << std::endl);
        m_macro_deps[outer_macro_defn_range].emplace(defn_range(MD));
    }
}
