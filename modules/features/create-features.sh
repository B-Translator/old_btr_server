#!/bin/bash

drush="drush --yes @dev"
destination="--destination=profiles/btranslator/modules/features"
features_export="$drush features-export $destination"

$features_export btranslator_layout $(cat layout.txt)
$features_export btranslator_content node_export_features

$features_export btranslator_disqus $(cat disqus.txt)
$features_export btranslator_sharethis $(cat sharethis.txt)
$features_export btranslator_janrain $(cat janrain.txt)
$features_export btranslator_drupalchat $(cat drupalchat.txt)
$features_export btranslator_simplenews $(cat simplenews.txt)
$features_export btranslator_mass_contact $(cat mass_contact.txt)
$features_export btranslator_invite $(cat invite.txt)