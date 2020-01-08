<?php

/**
 * @file
 * Handles the layout of the multichoice answering form.
 *
 * Variables available:
 * - $form.
 */

// We want to have the checkbox in one table cell, and the title in the next.
// We store the checkbox and the titles.
$options = $form['user_answer']['#options'];
$node = node_load($form['#parents'][TRUE]);

foreach ($node->alternatives as $key => $value) {
  if ($value['score_if_chosen'] == 1) {
	 	  $corrects[$value['id']] = $value['id']; 
	}
}
$feedback =  $node->feedback['value'];
$fullOptions = array();
$titles = array();
foreach ($options as $key => $value) {
  $fullOptions[$key] = $form['user_answer'][$key];
  $titles[$key] = $form['user_answer'][$key]['#title'];
  $fullOptions[$key]['#title'] = '';
  unset($form['user_answer'][$key]);
}
unset($form['user_answer']['#options']);
print drupal_render_children($form);
// We use the stored checkboxes and titles to generate a table for the
// alternatives.
foreach ($titles as $key => $value) {
  $row = array();
  $row[] = array('data' => drupal_render($fullOptions[$key]), 'width' => 35);
  $row[] = $value;
  if (in_array($key, $corrects)) {
    $rows[] = array('data' => $row, 'class' => array('multichoice-row id-'.$key.'  correct'));
  }else{
    $rows[] = array('data' => $row, 'class' => array('multichoice-row id-'.$key.' incorrect'));
  }
}
print theme('table', array('header' => array(), 'rows' => $rows));
// Render feedback
print theme('html_tag',
  array(
    'element' => array(
      '#tag' => 'div',
      '#attributes' => array(
        'id' => 'myModal',
        'class' => 'modal fade',
      ),
      '#value' => $feedback,
    ),
  )
);