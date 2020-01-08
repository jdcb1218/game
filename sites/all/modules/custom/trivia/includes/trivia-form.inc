<?php

/**
 * Implements hook_form().
 */

/**
 * Implements hook_form().
 */
function trivia_replay_form($form, &$form_state) {
  $form = array();
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Play Again'),
  );
  return $form;
}

/**
 * Implements hook_form().
 */
function trivia_replay_form_submit($form, &$form_state) {
	Global $user;
	$data = trivia_update_winner($user->uid);
	foreach ($data as $key => $value) {
	    if($value == $user->uid && $key != 'winner_uid'){
				$index = $key;
			}
		}
	switch ($index) {
		case 'uid':
			$opponent = 'uid_opponent';
			break;
		case 'uid_opponent':
			$opponent = 'uid';
			break;
	}
	// Delete Info Contrincante
	db_delete('quiz_node_results')
	->condition('uid', $data->$opponent)
	->execute();
	// Delete Info My Quiz
	db_delete('quiz_node_results')
	->condition('uid', $user->uid)
	->execute();
	// Redirect Go Play
	return drupal_goto('informacion-colombia');		  				
}

/**
 * Implements hook_form().
 */

function trivia_config($form, &$form_state) {

  $form['trivia'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration Trivia'),
    '#collapsible' => TRUE,
    '#group' => 'vertical_tabs',
  );

  $form['trivia']['contact_information'] = array(
	 '#markup' => t('This form clears the records in the (quiz_node_results_competition) Table'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Clean records'),
  );

  return $form;
}

/**
 * Implements hook_form().
 */

function trivia_config_submit($form, &$form_state) {
  $result = db_truncate('quiz_node_results_competition')->execute();
  return drupal_set_message(t('Successful Record Cleaning'), 'status', FALSE);
}
