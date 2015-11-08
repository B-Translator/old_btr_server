<?php
/**
 * @file
 * Form for backup/restore of B-Translator data.
 */

/**
 * Backup and restore B-Translator data.
 *
 * @return
 *   An array containing form items.
 */
function btrCore_backup() {
  $form = [
    // Backup.
    'data_backup' => [
      '#type' => 'fieldset',
      '#title' => t('Backup B-Translator Data'),
      '#description' => t('Backup users, translations and votes.'),

      'submit' => [
        '#value' => t('Backup'),
        '#type' => 'submit',
      ],
    ],

    // Restore.
    'data_restore' => [
      '#type' => 'fieldset',
      '#title' => t('Restote B-Translator Data'),
      '#description' => t('Restore users, translations and votes.'),

      'file' => [
        '#type' => 'file',
        '#title' => t('Backup File'),
        '#description' => t('Upload a backup file.'),
      ],

      'submit' => [
        '#value' => t('Restore'),
        '#type' => 'submit',
      ],
    ],
  ];

  return $form;
}

function btrCore_backup_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $op = $form_values['op'];

  if ($op == t('Backup')) {
    drupal_set_message('Backup');
  }

  if ($op == t('Restore')) {
    drupal_set_message('Restore');
  }
}
