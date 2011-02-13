<?php
// $Id$

/**
 * @file
 * Admin page callbacks for the boost module.
 */

/**
 * Form builder; Configure boost settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function boost_admin_expiration_settings() {

  $form['boost_ignore_flush'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ignore a cache flush command if cron issued the request.'),
    '#default_value' => variable_get('boost_ignore_flush', BOOST_IGNORE_FLUSH),
    '#description' => t(''),
  );
  $form['boost_expire_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove old cache files on cron.'),
    '#default_value' => variable_get('boost_expire_cron', BOOST_EXPIRE_CRON),
    '#description' => t(''),
  );

  return system_settings_form($form);
}
