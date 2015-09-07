<?php

/**
 * @file
 * template.php
 */

/**
 * Implement hook: theme_pager_previous()
 */
function btr_server_pager_previous($variables) {
  if ($variables['text'] == 'previous' ) $variables['text'] = '‹';
  return theme_pager_previous($variables);
}

/**
 * Implement hook: theme_pager_next()
 */
function btr_server_pager_next($variables) {
  if ($variables['text'] == 'next' ) $variables['text'] = '›';
  return theme_pager_next($variables);
}

/**
 * Implement hook: theme_pager_first()
 */
function btr_server_pager_first($variables) {
  if ($variables['text'] == 'first' ) $variables['text'] = '«';
  return theme_pager_first($variables);
}

/**
 * Implement hook: theme_pager_last()
 */
function btr_server_pager_last($variables) {
  if ($variables['text'] == 'last' ) $variables['text'] = '»';
  return theme_pager_last($variables);
}
