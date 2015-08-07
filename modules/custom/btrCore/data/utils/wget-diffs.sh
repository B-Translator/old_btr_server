#!/bin/bash
### Get the diffs of a project using wget and the REST API.

### get the arguments $lng and $nr
if [ $# -lt 3 ]
then
    echo "Usage: $0 origin project lng [nr]

    Get the diffs of a project using wget and the REST API.
    If 'nr' is missing, then the list of diffs will be retrieved instead.
    If 'nr' is '-', then the latest diffs (since the last snapshot)
    will be computed and returned (it will take longer to execute, since
    the diffs are calculated on the fly).

Examples:
    $0 KDE kdelibs sq
    $0 KDE kdelibs sq 1
    $0 KDE kdelibs sq 2
    $0 KDE kdelibs sq -
"
    exit 1
fi
origin=$1
project=$2
lng=$3
nr=$4
echo "$0 $origin $project $lng $nr"

base_url="https://dev.btranslator.org/"
#base_url="https://$lng.btranslator.org/"
#base_url="https://dev.btr.example.org/"
diff_url="$base_url/project/diff"
wget="wget -q --no-check-certificate"


if [ "$nr" = '' ]
then
    ### get the list of diffs
    $wget -O - $diff_url/$origin/$project/$lng
else
    ### get the diffs
    fname_diff=$origin-$project-$lng.$nr.diff
    fname_ediff=$origin-$project-$lng.$nr.ediff

    echo $wget -O $fname_diff $diff_url/$origin/$project/$lng/$nr
    $wget -O $fname_diff $diff_url/$origin/$project/$lng/$nr

    echo $wget -O $fname_ediff $diff_url/$origin/$project/$lng/$nr/ediff
    $wget -O $fname_ediff $diff_url/$origin/$project/$lng/$nr/ediff
fi
