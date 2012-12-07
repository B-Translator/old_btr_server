#!/bin/bash
### import the project 'misc/vocabulary'

cd $(dirname $0)

origin='misc'
project='vocabulary'
potname='vocabulary'

po_dir='../vocabulary'
file_pot="$po_dir/vocabulary.pot"
file_sq_po="$po_dir/vocabulary-sq.po"

./pot_import.php $origin $project $potname $file_pot
./po_import.php $origin $project $potname sq $file_sq_po

