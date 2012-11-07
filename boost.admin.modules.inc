<?php

/**
 * @file
 * Displays compatible modules for boost, descriptions of functionality and
 * links if not installed.
 */

/**
 * Returns a table listing of the status of recommended modules.
 */
function boost_compatible_output() {
  $modules_enabled = array();
  $modules_disabled = array();

  // Query from the database in case modules are already installed but not enabled
  $result = db_query("SELECT name, status FROM {system} WHERE type = 'module' ORDER BY weight ASC, name ASC");
  foreach ($result as $record) {
    if ($record->status == 1) {
      $modules_enabled[] = $record->name;
    }
    else {
      $modules_disabled[] = $record->name;
    }
  }

  $project_page = t('Project page');

  // list of compatible modules
  $recommended = array(
    'boost_crawler' => array(
      'title' => 'Boost Crawler',
      'link' => 'http://drupal.org/project/boost' ,
      'description' => t('Minimal crawler - expires and regenerates pages only when content is edited and on next cron run.'),
    ),
    'fast_404' => array(
      'title' => 'Fast 404',
      'link' => 'http://drupal.org/project/fast_404' ,
      'description' => t('Caches a static page for 404 errors, reducing server load'),
    ),
    'globalredirect' => array(
      'title' => 'Global Redirect',
      'link' => 'http://drupal.org/project/globalredirect',
      'description' => t('Redirects missing/ expired URI aliases back to home page, saves boost generation of deprecated aliases'),
    ),
    'httprl' => array(
      'title' => 'HTTP Parallel Request & Threading Library',
      'link' =>  'http://drupal.org/project/httprl',
      'description' => t('Required by boost crawler, performs http requests to regenerate expired pages.'),
    ),
    'expire' => array(
      'title' => 'Cache Expiration',
      'link' => 'http://drupal.org/project/expire',
      'description' => t('Expire specific pages of the cache immediately when content is added or modified. Also required by the Boost crawler, to crawl expired content after expiration.'),
    ),
  );

  ksort($recommended);

  // uses array_intersect as array_intersect_key only came in PHP > 5.1
  $installed = array_intersect($modules_enabled, array_keys($recommended));
  $disabled = array_intersect($modules_disabled, array_keys($recommended));
  $not_installed = array_diff( array_diff( array_keys($recommended), $installed), $disabled );

  // prepare the table
  $header = array('Module', 'Status', 'Description');

  $rows = array();

  foreach ($recommended as $module => $data) {
    $status = in_array($module, $not_installed) ? 'Not Installed' : (in_array($module, $disabled) ? 'Disabled' : 'Enabled' ) ;
    $trclass = in_array($module, $not_installed) ? 'info' : (in_array($module, $disabled) ? 'warning' : 'ok' ) ;
    $module_link = (in_array($module, $not_installed) ? '<div style="float:right">' . l($project_page, $data['link']) . '<br />' . l($data['link'], $data['link']) . '</div>' : '' ) ;

    $rows[] = array(
      'data' => array(
        $data['title'],
        $status,
        $data['description'] . $module_link,
      ),
      'class' => array($trclass),
      'no_striping' => TRUE,
    );
  }

  $output = theme('table', array('attributes' => array('class' => array('system-status-report')), 'header' => $header, 'rows' => $rows));

  return array(
   'my_page' => array(
      '#markup' => $output,
    ),
  );
}

