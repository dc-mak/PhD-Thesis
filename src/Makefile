.SUFFIXES: .pdf .tex .bib $(SUFFIXES)

PREFIX := cn

FLAGS := -quiet
ifneq (,$(findstring B,$(MAKEFLAGS)))
    FLAGS := $(FLAGS) -g
endif

BUILD := _build

GEN := $(BUILD)/_gen

CACHE := $(BUILD)/ott.cache

OTTS := mucore.ott explicit.ott inference.ott operational.ott misc.ott
OTTS := $(addprefix ott/, $(OTTS))

PDFS := $(BUILD)/defns.pdf $(BUILD)/soundness.pdf

all: $(PDFS) $(GEN)/mucore.ml

.PHONY: all

.SECONDEXPANSION:
$(PDFS):$(BUILD)/%.pdf: $(GEN)/$$*.tex \
    $(GEN)/$(PREFIX)_included.tex \
    $(GEN)/$(PREFIX)_override.tex \
    $(GEN)/$(PREFIX)_drulenames.tex | $(BUILD)
	latexmk -quiet $< $(FLAGS) \
	    || (cat $(BUILD)/$(basename $(notdir $<)).log; exit 1)
	@grep "Warning" $(BUILD)/$(basename $(notdir $<)).log || true

$(GEN)/soundness.tex: ott/soundness.mng $(CACHE) | check_rule_diff $(GEN)
	ott -readsys $(CACHE) -tex_name_prefix $(PREFIX) -tex_filter $< $@ | tac

# Subs\_Pat\_Value'\_Sym turns |-> \newcommand{\SubsPatValueSym}{\textsc{\Subs\_\allowbreak{}Pat\_\allowbreak{}Value'\_\allowbreak{}Sym}}
$(GEN)/$(PREFIX)_drulenames.tex: $(GEN)/defns.drulenames | $(GEN)
	@echo "Generating $@"
	@awk '{ x=$$0; gsub(/[^a-zA-Z]/, ""); gsub(/_/, "_\\allowbreak{}", x); print "\\newcommand{\\" $$0 "}{\\textsc{" x "}}"; }' $^ > $@

.PHONY: check_rule_diff

# Subs\_Pat\_Value'\_Sym                    |-> {\SubsPatValueSym}{}}
# \step{<0>\d\+}{\case{\SubsPatValueSym}{}} |-> {\SubsPatValueSym}{}}
check_rule_diff: $(GEN)/defns.drulenames | $(GEN)
ifneq ($(SKIP_CHECK),y)
	@echo "Checking for rule differences (run 'make SKIP_CHECK=y <args>' to skip) "
	@awk '{ gsub(/[^a-zA-Z]/, ""); print "{\\" $$0 "}{}}"; }' $^ > $@
	@awk -F'case' '/^\\step{<0>/{ print $$2; }' ott/soundness.mng | diff -u --color - $@
	@rm $@
endif

.PHONY: append_rule_cases

# Subs\_Pat\_Value'\_Sym |-> \step{<0>\d\+}{\case{\SubsPatValueSym}{}}
append_rule_cases: $(GEN)/defns.drulenames | $(GEN)
	@if [ ! -z "$$( git status ott/soundness.mng --porcelain )" ]; then echo "save/stash ott/soundness.mng first"; exit 1; fi
	@echo 'Appending \step{<0>$$RULE_NUM}{\case{$$RULE}{}}'
	@awk '{ gsub(/[^a-zA-Z]/, ""); print "\\step{<0>" NR "}{\\case" "{\\" $$0 "}{}}"; }' $^ > $@
	@sed '1,/^\end{document}$$/d' < ott/soundness.mng > old_cases
	@sed -i".tmp" '/^\\end{document}$$/q' ott/soundness.mng
	@cat $@ >> ott/soundness.mng && rm $@

# {\cndrulename{Subs\_Pat\_Value'\_Sym}}{} |-> Subs\_Pat\_Value'\_Sym
$(GEN)/defns.drulenames: $(GEN)/$(PREFIX)_included.tex | $(GEN)
	@echo "Generating $@"
	@sed -n 's/^{\\$(PREFIX)drulename{\(.*\)}}{}%/\1/p' $^ > $@

$(GEN)/$(PREFIX)_override.tex: ott/override.tex | $(GEN)
	touch empty.ott
	ott -tex_wrap false -signal_parse_errors true \
	    -tex_name_prefix $(PREFIX) -tex_filter $< $@ empty.ott
	rm empty.ott

$(GEN)/mucore.ml: ott/mucore.ott | $(GEN)
	patch -p1 < ott/ocaml_gen.patch
	ott -o $@ $^
	patch -p1 -R < ott/ocaml_gen.patch

$(GEN)/defns.tex: ott/defns.tex $(CACHE) | check_defns_diff $(GEN)
	ott -readsys $(CACHE) -tex_name_prefix $(PREFIX) -tex_filter $< $@

.PHONY: check_defns_diff

check_defns_diff: $(GEN)/$(PREFIX)_included.tex
	@echo "Checking for definitions differences"
	@grep -o '^\\$(PREFIX)defns[a-zA-Z]\+' $^ | sed '$$d' > $@
	@grep -o '^\\$(PREFIX)defns[a-zA-Z]\+' ott/defns.tex | diff -u --color - $@
	@rm $@

.PHONY: out_hack
out_hack: $(OTTS)
	sed -i".tmp" '/% OUT_HACK.*/{n;N;N;d;}' $(OTTS)
	for i in $(OTTS); do ./out_hack.awk -i inplace $$i; done

$(GEN)/$(PREFIX)_included.tex: $(CACHE) | $(GEN)
	ott -readsys $(CACHE) \
	    -o $@ \
	    -tex_wrap false \
	    -tex_name_prefix $(PREFIX) \
	    -tex_show_categories true \
	    -tex_suppress_category X \
	    $(shell awk -F' ' '/{{ com Ott-hack, ignore }}/{ print "-tex_suppress_ntr " $$1; }' $(OTTS)) \
	    -tex_suppress_ntr terminals \
	    -tex_suppress_ntr user_syntax \
	    -tex_suppress_ntr judgement

$(CACHE): %: $(OTTS) | $(BUILD)
	ott -signal_parse_errors true -generate_aux_rules false $(addprefix -i , $^) -writesys $@ | tac

$(BUILD) $(GEN): %:
	mkdir -p $@

.PHONY: clean

clean:
	rm -rf soundness.mng.pfx old_cases $(BUILD)
