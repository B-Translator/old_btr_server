#!/bin/bash

data_root="$1"
oo_l10n="$data_root/oo-l10n"
oo_po="$data_root/oo-po"

if [ ! -d $oo_l10n ]; then
    echo -n "co l10n..."
    cd $data_root
    (cvs -d:pserver:anoncvs@anoncvs.services.openoffice.org:/cvs co -P -d oo-l10n l10n/l10n/source > /dev/null || true) 2>&1
    echo "done."
else
    cd $oo_l10n
    echo -n "up l10n..."
    (cvs up > /dev/null || true) 2>&1
    echo "done."
fi

if [ ! -d $oo_po ]; then
    mkdir $oo_po
fi

cd $oo_po
echo -n "clean..."
rm -rf *
echo "done"

echo -n "get en-US..."
wget -o /dev/null ftp://ftp.linux.cz/pub/localization/OpenOffice.org/3.0.0/GSI/en-US.sdf
echo "done."

cd $oo_l10n

for d in *; do
    if [ ! -f "$d/localize.sdf" ]; then
	continue
    fi

    echo -n "merging $d..."
    cat "$oo_po/en-US.sdf" > "$oo_po/full.sdf"
    sed '/^#/d' < "$d/localize.sdf" >> "$oo_po/full.sdf"
    echo "done."

    echo -n "converting $d..."
    oo2po --progress none --duplicates=merge -l $d "$oo_po/full.sdf" "$oo_po/$d" > /dev/null
    echo "done."
done
