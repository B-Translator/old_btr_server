#!/bin/bash

drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_layout $(cat layout.txt)
drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_content node_export_features
drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_disqus $(cat disqus.txt)

lng=$(drush @dev vget l10n_feedback_translation_lng --exact --format=json)
lng=${lng:1:-1}  # remove the double quotes
drush --yes @dev fe --destination=profiles/btranslator/modules/features btranslator_$lng $(cat custom.txt)
