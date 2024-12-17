std::optional<fs::path> simplify(tl::ClangTool &tool,
                                 const std::unordered_set<std::string> &roots) {

    std::optional<KeptLines> kept_lines;
    ReachabilityAnalyzerFactory analyzer_factory(kept_lines, roots);
    const auto errs = tool.run(&analyzer_factory);
    if (errs != 0 || !kept_lines)
        return {};

    const auto result = gen_tmp_dir();
    for (const auto &it : *kept_lines) {

        const auto &[filename, file_lines] = it;
        CTC_DEBUG(std::cerr << "Outputting: " << filename << std::endl);

        auto ofs = create(result, fs::path(filename));

        // open file and iterate line by line
        std::ifstream iss(filename);
        std::string line;

        for (unsigned int i = 0; std::getline(iss, line); ++i) {
            const auto marked_i = i < file_lines.size() && file_lines[i];
            if (!marked_i)
                ofs << "//-";
            ofs << line << std::endl;
        }
    }

    return result;
}
