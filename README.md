# KACTL

This repo hosts KACTL, [KTH](https://en.wikipedia.org/wiki/KTH_Royal_Institute_of_Technology)'s ICPC team reference document.
It consists of 25 pages of copy-pasteable C++ code, for use in ICPC-style programming competitions.

See [kactl.pdf](https://github.com/kth-competitive-programming/kactl/blob/master/kactl.pdf) for the final, browsable version,
and [content/](https://github.com/kth-competitive-programming/kactl/tree/master/content) for raw source code.

## Aspirations

KACTL algorithms should be: useful, short, fast enough, well tested, and if relevant, readable and easy to modify.
They should *not* be overly generic, since code is manually typed and that just adds overhead.
Due to space issues, we also exclude algorithms that are very common/simple (e.g., Dijkstra), or very uncommon (general weighted matching).

If you feel that something is missing, could be cleaned up, or notice a bug, please file an issue or [send a pull request](https://help.github.com/articles/fork-a-repo/)!

## Customizing KACTL

While KACTL is usable as is, it's also easy to modify if you want to create a personalized copy.
In particular, you may want to change the cover page, or make your own choice of algorithms to include --
due to space concerns, not all algorithms in the repo are included in the pdf.
You may also want to enable colored syntax highlighting.

`content/kactl.tex` is the main file of KACTL, and can be edited to change team name, logo, syntax highlighting, etc.
It imports `chapter.tex` files from each of the `content/` subdirectories, which define the contents of each chapter.
These include source code, text and math in the form of LaTeX.
To add/remove code from a chapter, add/remove a corresponding `\kactlimport` line from the `chapter.tex` file.
For nicer alignment you might want to insert `\hardcolumnbreak`, `\columnbreak` or `\newpage` commands,
though this is usually only done before important contests, and not on master.
The algorithms that are not included in the pdf are left commented out in `chapter.tex`.

To build KACTL, type `make kactl` (or `make fast`) on a \*nix machine -- this will update `kactl.pdf`.
(Windows might work as well, but is not tested.) `doc/README` has a few more notes about this.

## Coding style

KACTL uses a relatively terse coding style, with a handful of macros/typedefs defined in the
[template](https://github.com/kth-competitive-programming/kactl/blob/master/content/contest/template.cpp) that help shorten the code.
Line width is 63 chars, with tabs for indentation (tab = 2 spaces in the pdf).

Each algorithm contains a header with the author of the code, the date it
was added, a description of the algorithm, its testing status, and preferably also
source, license and time complexity.

kactl.pdf is to be kept to 25 pages + cover page.
Occasionally the generated kactl.pdf is committed to the repo for convenience, but not too often because it makes git operations slower.

## Testing

KACTL aims for a high level of confidence in algorithm correctness.
Testing is done both on online judges and (for newer algorithms) with stress tests
that compare output to a more naive algorithm for a large amount of randomly generated cases.
These tests live in the `stress-tests` directory, and are run with CI on every commit.

`old-unit-tests` contains a couple of broken unit tests, last touched about ten years ago.

## License

As usual for competitive programming, the licensing situation is a bit unclear.
Many source files are marked with license (we try to go with
[CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)), but many also aren't.
Presumably good will is to be assumed from other authors, though, and in many cases permission should not be needed since the code is not distributed.
To help trace things back, sources and authors are noted in source files.

Everything in `stress-tests` is implicitly CC0, except reference implementations taken from around the Internet.
