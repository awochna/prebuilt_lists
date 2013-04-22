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
  return;
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
