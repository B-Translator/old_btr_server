
Drupal.behaviors.replaceBtrUiURLs = function(context) {
  // Act on links if we have URL replacements to do.
  if (Drupal.settings.btrUiURLs) {
    for (var url in Drupal.settings.btrUiURLs) {
      // Look for links with this exact URL and replace with extended version.
      // This ensures we keep filter values while switching tabs.
      $('a[href=' + url +']', context).not('.filter-exclude').attr('href', Drupal.settings.btrUiURLs[url]);
    }
  }
}
