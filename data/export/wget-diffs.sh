#!/bin/bash
### Get the diffs of a project using wget and the REST API.

base_url="https://l10n-sq.org/"
diff_url="$base_url/translations/project/diff"
wget="wget -q --no-check-certificate"


### get the arguments $lng and $nr
if [ $# -lt 3 ]
then
    echo "Usage: $0 origin project lng [nr]

    Get the diffs of a project using wget and the REST API.
    If 'nr' is missing, then the list of diffs will be retrieved instead.

Examples:
    $0 misc pingus sq
    $0 misc pingus sq 1
    $0 misc pingus sq 2
"
    exit 1
fi
origin=$1
project=$2
lng=$3
nr=$4


if [ "$nr" = '' ]
then
    $wget -O - $diff_url/$origin/$project/$lng
else
    fname_diff=$origin-$project-$lng.$nr.diff
    fname_ediff=$origin-$project-$lng.$nr.ediff

    echo $wget -O $fname_diff $diff_url/$origin/$project/$lng/$nr
    $wget -O $fname_diff $diff_url/$origin/$project/$lng/$nr

    echo $wget -O $fname_ediff $diff_url/$origin/$project/$lng/$nr/ediff
    $wget -O $fname_ediff $diff_url/$origin/$project/$lng/$nr/ediff
fi

