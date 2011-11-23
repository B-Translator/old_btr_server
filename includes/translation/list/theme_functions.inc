<?php

/**
 * Theme functions.
 */

/**
 * Main theme function for translation table.
 */
function theme_l10n_suggestions_translate_table($variables) {

  $element = $variables['element'];
  $header = array(
    array(
      'data' => t('Source text'),
      'colspan' => 2,
    ),
    t('Translations'),
  );

  $rows = array();

  foreach (element_children($element) as $key) {
    $lng = $element[$key]['#langcode'];
    $hash = $element[$key]['#string']->hash;
    $rows[] = array(
      array(
        'class' => array('sid'),
        'data' => l('#', "translation/get/$lng/$hash", array(), array('attributes' => array('title' => t('Direct and permanent link to this string.')))),
      ),
      array(
        'class' => array('source'),
        'data' => theme('l10n_suggestions_translate_source', array('element' => $element[$key])),
      ),
      array(
        'class' => array('translation'),
        'data' => theme('l10n_suggestions_translate_translation_list', array('element' => $element[$key])),
      ),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('l10n-table'))));
}

/**
 * Theme function for a source cell in the translation table.
 */
function theme_l10n_suggestions_translate_source($variables) {
  $element = $variables['element'];
  $output = theme('l10n_suggestions_translate_actions', array('element' => $element['source']));
  //$filter_match = ($element['filters_match']['#value'] ? ' filter-match' : ' filter-no-match');
  $filter_match = ' filter-no-match';
  $output .= '<label class="l10n-string' . $filter_match . '">' . drupal_render($element['source']['string']) . '</label>';
  $output .= theme('l10n_suggestions_in_context', array('source' => $element['#string']));

  $output .= '<div class="l10n-usage"><a href="' . url('translation/source-details/' . $element['#string']->pid) . '" class="l10n-more-link" title="' . t('Show list of projects and releases where this text is used.') . '">' . t('Show related projects') . '</a><div class="l10n-more-info"></div></div>';

  /** TODO: Improve alternatives in other languages.
  $output .= drupal_render($element['alternatives']);
  */

  return $output;
}

/**
 * Theme appropriate actions for the given string element.
 */
function theme_l10n_suggestions_translate_actions($variables) {
  $element = $variables['element'];
  $actions = '';
  foreach (array('declined', 'edit') as $type) {
    if (isset($element[$type])) {
      $actions .= '<li class="' . $type . '">' . drupal_render($element[$type]) . '</li>';
    }
  }
  if (!empty($actions)) {
    return '<ul class="actions">' . $actions . '</ul>';
  }
  else {
    return '';
  }
}

/**
 * Theme context information for source strings.
 *
 * @param $string
 *   Source string object.
 */
function theme_l10n_suggestions_in_context($variables) {
  $string = $variables['source'];
  if (!empty($string->context)) {
    return '<div class="string-context">' . t('in context: @context', array('@context' => $string->context)) . '</div>';
  }
  return '';
}

/**
 * Theme a suggestion/translation.
 */
function theme_l10n_suggestions_translate_translation($variables) {
  $element = $variables['element'];
  if (!isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array();
  }
  $element['#attributes']['class'][] = 'clearfix';
  $element['#attributes']['class'][] = 'translation';

  // Add is-selectable and is-declinable helpers for JS.
  if (!$element['approved']['#disabled']) {
    $element['#attributes']['class'][] = 'is-selectable';
  }
  if (isset($element['declined'])) {
    $element['#attributes']['class'][] = 'is-declinable';
  }

  // Add information on whether this matched the filter.
  if ((int) $element['approved']['#return_value'] > 0) {
    //$filters_match = ($element['filters_match']['#value']) ? 'filter-match' : 'filter-no-match';
    $filters_match = 'filter-no-match';
    $element['#attributes']['class'][] = $filters_match;
  }

  switch ($element['approved']['#return_value']) {
    case 'new':
      $element['#attributes']['class'][] = 'new-translation';
      break;
    case '0':
      $element['#attributes']['class'][] = 'no-translation';
      // Fallthrough.
    default:
      if ($element['approved']['#value'] !== '') {
        $element['#attributes']['class'][] = 'is-approved default';
      }
  }

  $output = '<li' . drupal_attributes($element['#attributes']) . '>';
  $output .= theme('l10n_suggestions_translate_actions', array('element' => $element));
  // Add the radio box to pick the approved translation.
  $output .= drupal_render($element['approved']);

  if (isset($element['author'])) {
    $output .= '<div class="author">' . drupal_render($element['author']) . '</div>';
  }
  //TODO: Improve displaying of vote count and the voters.
  if (isset($element['votes'])) {
    $output .= '<div class="votes">' . drupal_render($element['votes']) . '</div>';
  }

  if (isset($element['value'])) {
    $output .= drupal_render($element['value']);
  }
  return $output  . '</li>';
}

/**
 * Theme a radio button to pick the approved translation.
 */
function theme_l10n_suggestions_translate_radio($variables) {
  $element = $variables['element'];
  _form_set_class($element, array('form-radio'));
  $output = '<input type="radio" ';
  $output .= 'id="' . $element['#id'] . '" ';
  $output .= 'name="' . $element['#name'] . '" ';
  $output .= 'value="' . $element['#return_value'] . '" ';
  $output .= $element['#checked'] ? ' checked="checked" ' : ' ';
  $output .= drupal_attributes($element['#attributes']) . ' />';

  if (isset($element['#title'])) {
    $output .= '<label class="l10n-string" for="' . $element['#id'] . '">' . $element['#title'] . '</label>';
  }
  return $output;
}

/**
 * Theme a list of suggestions for a string.
 */
function theme_l10n_suggestions_translate_translation_list($variables) {
  $element = $variables['element'];
  $output = '<ul>';
  foreach (element_children($element) as $child) {
    if (is_numeric($child) || $child == 'new') {
      $output .= drupal_render($element[$child]);
    }
  }
  $output .= '</ul>';
  return $output;
}

?>