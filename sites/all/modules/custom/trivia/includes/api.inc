<?php

function trivia_reply_page() {
  return theme('trivia_template');
}

function trivia_manage_players($edit, $account, $category){
  // Consulta si hay usuarios existentes
  $result = db_select('quiz_node_results_competition', 'c')
    ->fields('c')
    ->condition('uid', '', '<>')
    ->condition('uid_opponent', '', '=')
    ->execute()
    ->fetchAssoc();
  // Si existe un registro existente  Actualiza Registrando al  Segundo Jugador
  if($result){
    $rs =  db_update('quiz_node_results_competition')
        ->fields(array(
          'uid_opponent' => $account->uid
        ))
        ->condition('uid', $result['uid'], '=')
        ->execute(); 
  }else{ // Si no existe registro existente crea un nuevo Jugador
      $nid = db_insert('quiz_node_results_competition') // Table name no longer needs {}
        ->fields(array(
          'uid' => $account->uid,
          'created' => REQUEST_TIME,
      ))->execute();
  }
}

function ajax_reply_callback(){
  Global $user;
 // My Ultimo resultado Results.
  $result = db_select('quiz_node_results', 'c')
    ->fields('c')
    ->condition('uid', $user->uid,'=')
    ->orderBy('c.time_end', 'DESC')
    ->execute()
    ->fetchAssoc();

  $my_time = $result['time_end']-$result['time_start'];
  // Obtener Array match (Palyers). 
  $match = db_select('quiz_node_results_competition', 'n')
	->fields('n')
	->condition(
	 db_or()
	   ->condition('uid', $user->uid, '=')
	   ->condition('uid_opponent', $user->uid, '=')
	 )
	->execute()
	->fetchAll();
  $match = reset($match); 


	foreach ($match as $key => $value) {
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

  // @Id del Contricante  $match['uid_opponent']
  // Chequear Si mi Contrincante ya acabo. 
  $rs_opponent = db_select('quiz_node_results', 'c')
    ->fields('c')
    ->condition('uid', $match->$opponent,'=')
    ->condition('is_evaluated', true, '=')
    ->execute()
    ->fetchAssoc();

   if ($rs_opponent == FALSE) {
  		print(t('Give it a moment'));
    }else{
  	  $result_op = db_select('quiz_node_results', 'c')
    	    ->fields('c')
    	    ->condition('uid', $match->$opponent,'=')
    	    ->orderBy('c.time_end', 'DESC')
    	    ->execute()
    	    ->fetchAssoc();
  	  if($result_op['score'] < $result['score']) {
          trivia_update_winner($user->uid);
  		    print('winning-player' . '/' . $user->uid);
  	  }if($result_op['score'] > $result['score']){
  		    trivia_update_winner($match->$opponent);
          print('winning-player' . '/' . $match->$opponent);
  	  }elseif($result_op['score'] == $result['score']){
  		     $opt_time = $result_op['time_end']-$result_op['time_start'];
      		 if($my_time < $opt_time){
              trivia_update_winner($user->uid);
      		   	print('winning-player' . '/' . $user->uid);
      		 }else{
               trivia_update_winner($match->$opponent);
      		   	 print('winning-player' . '/' . $match->$opponent);
      		 }
  	  }
    } 
}

function trivia_alter_question_true_false(&$form, &$form_state, $form_id){
    $key_question = array_keys($form['question']); 
    $nid_question = $key_question[FALSE];
    $node_tf = node_load($nid_question);
    
    if (isset($form['question'][$nid_question]['answer']['#options'])) {
      $data_feedback = theme('html_tag',
        array(
          'element' => array(
            '#tag' => 'div',
            '#attributes' => array(
              'id' => 'myModal',
              'class' => 'modal fade',
            ),
            '#value' => $node_tf->feedback['value'],
          ),
        )
      );

     $img_true = theme('image', array('path' => 'sites/all/themes/custom/trivia/img/img-true-trans.png', 
                          'attributes' => array('class' => 'ico-true', 'id' => 'true-ico')
                 ));

     $img_false = theme('image', array('path' => 'sites/all/themes/custom/trivia/img/img-false-trans.png', 
                          'attributes' => array('class' => 'ico-false', 'id' => 'false-ico')
                  ));

      foreach ($form['question'][$nid_question]['answer']['#options'] as $key => $value) {
         $img_question = ($key == 0) ?  $img_false: $img_true;
         if ($key == $node_tf->correct_answer) {
            $render = array('#type' => 'item',
                            '#prefix' => '<div class="correct">',
                            '#markup' => $img_question,
                            '#suffix' => '<div class="img-borde"></div></div>', 
            );
          }else{
             $render = array('#type' => 'item',
                              '#prefix' => '<div class="incorrect">',
                              '#markup' => $img_question,
                              '#suffix' => '<div class="img-borde"></div></div>', 
             ); 
          }
       $form['question'][$nid_question]['answer']['#options'][$key] = render($render); 
      }
      $form['question'][$nid_question]['answer']['#options']['feedback'] = render($data_feedback);
    }  
}

function trivia_update_winner($uid){
  // Get Informacion Dupla
  $match['storage'] = db_select('quiz_node_results_competition', 'n')
    ->fields('n')
    ->condition(
     db_or()
       ->condition('uid', $uid, '=')
       ->condition('uid_opponent', $uid, '=')
     )
    ->execute()
    ->fetchAll();
  $data = reset($match['storage']);
  // Update Winner Dupla
  $rs = db_update('quiz_node_results_competition')
          ->fields(array(
          'winner_uid' => $uid
        ))
        ->condition('id', $data->id, '=')
        ->execute(); 
  return $data;
}

function trivia_label_player_game(){
    $id = db_insert('quiz_starts_duplas')
      ->fields(array(
        'created' => REQUEST_TIME,
    ))->execute();
}

function trivia_reidrect(){
  if (current_path() == 'node/12/take/ajax_logout') {
      drupal_goto('user/logout');
  }

  if (arg(1) == 'node' && is_numeric(arg(2)) && arg(3) == 'take' && arg(4) == 'ajax_logout') {
     drupal_goto('user/logout');
  }

  if (drupal_session_started() == FALSE && current_path() != 'user/register' && current_path() != 'user') {
     drupal_goto('<front>');
  }
}