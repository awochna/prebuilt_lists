<?php

/**
 * Admin Pages for Prebuilt Lists, allows for showing all lists and creating new ones.
 */
 
/**
 * Menu callback for admin/structure/prebuilt-lists
 */

function prebuilt_lists_list() {
  //TODO: Query Database to select all in list table. Issue # 6
  //TODO: Add pagination for lots of lists. Issue #7
  
  $query = db_select('prebuilt_lists')
    ->extend('PagerDefault')
    ->orderBy('list_id')
    ->fields('name', 'description', 'path')
    ->limit(10);
    
  $result = $query->execute();
  
  foreach($result as $row) {
    $rows[] = array(
      l($row->name, $row->path),
      'description' => $row->description,
      l('Edit', $row->path . '/edit'),
      l('Delete', $row->path . '/delete'),
    );
  }
  
  $header = array('Name', 'Description', 'Edit', 'Delete');
  
  $output = theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager');
  
  return $output;
};

/**
 * Wrap new list page in a callback and add some helping header text.
 */

function new_prebuilt_lists_page() {
  $build = array(
    'header_text' => array(
      '#type' => 'markup',
      '#markup' => '<p>' . t('Create a new list for use later by filling out the form below.') . '</p>',
    ),
    'new_list' => drupal_get_form('prebuilt_lists_new'),
  );
};

/**
 * Menu callback for admin/structure/prebuilt-lists/new
 */

function prebuilt_lists_new($form, &$form_submit) {
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => t('Title or Name for this list.'),
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $prebuilt_lists['machine_name'],
    '#maxlength' => 200,
    '#required' => TRUE,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#description' => t('Description of this list, helps other people (and yourself) understand the reasoning behind its creation.')
  );
  $form['contents'] = array(
    '#type' => 'textarea',
    '#description' => t('<strong>Key-value pairs MUST be specified as "safe_key|Some readable option"</strong>. Use of only alphanumeric characters and underscores is recommended in keys. One option per line. Option groups may be specified with <Group Name>. <> can be used to insert items at the root of the menu after specifying a group.')
  );
  return $form;
};

function prebuilt_lists_new_validate($form, &$form_state) {
  // Validate the $form[machine_name] by making sure it doesn't already exist in the database.
  return;
};

/**
 * Simple function to add the newly created list to the databse, to be called after prebuilt_lists_new_validate()
 */

function add_prebuilt_lists() {
  global $user;
  
  $list_id = db_insert('prebuilt_lists')
    ->fields(array(
      'name' => 'name',
      'machine_name' => 'machine_name',
      'description' => 'description',
      'contents' => 'contents',
      'path' => 'admin/structure/prebuilt-lists' . $machine_name,
      'uid' => $user->uid,  
    ))
    ->execute();
  return $list_id;
};

/**
 * Function to delete prebuilt lists, should be available through prebuilt_lists_list and permission restricted.
 */

function delete_prebuilt_lists($selection) {
  $deleted = db_delete('prebuilt_lists')
    ->condition('list_id', $selection)
    ->execute();
    
  return $deleted;
};
