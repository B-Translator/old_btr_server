#!/bin/bash

drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_layout $(cat layout.txt)
drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_conte
nt node_export_features
