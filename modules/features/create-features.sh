#!/bin/bash

drush="drush --yes @dev"
destination="--destination=profiles/btranslator/modules/features"

$drush fe $destination btranslator_layout $(cat layout.txt)
$drush fe $destination btranslator_content node_export_features

$drush fe $destination btranslator_disqus $(cat disqus.txt)
$drush fe $destination btranslator_sharethis $(cat sharethis.txt)
$drush fe $destination btranslator_janrain $(cat janrain.txt)
$drush fe $destination btranslator_drupalchat $(cat drupalchat.txt)