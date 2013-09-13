#!/usr/bin/env bash
#
# Generate documentation for Phoenix.
#
# At the risk of pedantry: shell scripting is an involved topic, and every wart
# and lump in this script has a purpose. Recommended reading:
#
# * http://mywiki.wooledge.org/BashFAQ/028
# * http://mywiki.wooledge.org/UsingFind

set -o errexit
set -o nounset
readonly _destdir='../gen'
readonly script_name='gen-docs.sh'
readonly usage="usage: $script_name <srcdir> [<destdir>]

$script_name generates documentation for Phoenix. It copies files from <srcdir>
to <destdir>, compiling markdown and dot files in the process.

<srcdir>
    The directory containing documentation.
<destdir>
    Default: <srcdir>/$_destdir
    The directory into which files are placed."

# Fetch arguments from user. Set `srcdir` and `destdir`.
if [ -z "${1:-}" ]; then
    echo "$usage"
    exit 1
else
    readonly srcdir="`readlink -e "$1"`"
fi
if [ -z "${2:-}" ]; then
    readonly destdir="$srcdir/$_destdir"
else
    readonly destdir="`readlink -e "$2"`"
fi

# Copy and compile files.
#
# $0: absolute path of file being compiled
# $1: absolute path of destination directory
find "$srcdir" -maxdepth 1 -type f -name '*.md' -exec sh -c '
    readonly filename="`basename "$0"`"
    markdown "$0" > "$1/${filename%md}html"
' {} "$destdir" ';' -o -type f -name '*.dot' -exec sh -c '
    readonly filename="`basename "$0"`"
    dot -Tsvg -o "$1/${filename%dot}svg" "$0"
' {} "$destdir" ';' -o -type f -exec sh -c '
    readonly filename="`basename "$0"`"
    cp "$0" "$1/$filename"
' {} "$destdir" ';'
