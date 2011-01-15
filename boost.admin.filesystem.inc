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
function boost_admin_filesystem_settings() {

  $form['boost_root_cache_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Root cache directory'),
    '#default_value' => variable_get('boost_root_cache_dir', BOOST_ROOT_CACHE_DIR),
  );
  $form['boost_normal_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Normal cache directory'),
    '#default_value' => variable_get('boost_normal_dir', BOOST_NORMAL_DIR),
  );
  $form['boost_char'] = array(
    '#type' => 'textfield',
    '#title' => t('Character replacement for "?" in the URL'),
    '#default_value' => variable_get('boost_char', BOOST_CHAR),
  );
  $form['boost_permissions_file'] = array(
    '#type' => 'textfield',
    '#title' => t('Files: Enter in a 4 digit number (octal) that will be used by !link. Example 0664', array('!link' => l(t('chmod()'), 'http://php.net/chmod'))),
    '#default_value' => variable_get('boost_permissions_file', BOOST_PERMISSIONS_FILE),
    '#description' => t('Sometimes because of funky servers you need it use a different file mode then the default.'),
  );
  $form['boost_permissions_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Directories: Enter in a 4 digit number (octal) that will be used by !link. Example 0775', array('!link' => l(t('chmod()'), 'http://php.net/chmod'))),
    '#default_value' => variable_get('boost_permissions_dir', BOOST_PERMISSIONS_DIR),
    '#description' => t('Sometimes because of funky servers you need it use a different file mode then the default.'),
  );

  return system_settings_form($form);
}
