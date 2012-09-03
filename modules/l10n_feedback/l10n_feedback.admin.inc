<?php
/**
 * @file
 * Administrative page code for the l10n_feedback module.
 *
 */
/**
 * General configuration settings for the module l10n_feedback.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function l10n_feedback_config() {

  $form['config'] = array(
    '#type'  => 'fieldset',
    '#title' => t('B-Translator configuration options'),
  );

  $voting_mode_options = array(
    'single'   => t('Single'),
    'multiple' => t('Multiple'),
  );
  $voting_mode_description = t('
      When voting mode is <em>Single</em>, only one translation
      can be voted as suitable for each string. When voting mode is
      <em>Multiple</em>, more than one translation can be selected
      as suitable for each string. <br/>
      <strong>Note:</strong> Switching back from <em>Multiple</em>
      to <em>Single</em> may have a bad impact on the existing votes.
  ');

  $form['config']['l10n_feedback_voting_mode'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select Voting Mode'),
    '#default_value' => variable_get('l10n_feedback_voting_mode', 'single'),
    '#options'       => $voting_mode_options,
    '#description'   => $voting_mode_description,
  );

  $languages = l10n_feedback_get_languages();
  foreach ($languages as $code => $lang)  $lang_options[$code] = $lang['name'];
  unset($lang_options['en']);
  $form['config']['l10n_feedback_default_lng'] = array(
    '#type' => 'select',
    '#title' => t('Default Translation Language'),
    '#description' => t('The default language of translations, which is used wherever the translations language in not specified (for example for the guest users).'),
    '#options' => $lang_options,
    '#default_value' => variable_get('l10n_feedback_default_lng', 'fr'),
  );

  return system_settings_form($form);
}  //  End of l10n_feedback_config().
