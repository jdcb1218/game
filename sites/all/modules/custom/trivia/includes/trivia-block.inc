<?php


 /**
  * Implements hook_block_info().
  */
 function trivia_block_info() {

   $blocks['logo'] = array(
     'info' => t('Logo Subtheme @boostrap'),
     'cache' => DRUPAL_NO_CACHE
   );

   $blocks['time'] = array(
     'info' => t('Time trivia'),
     'cache' => DRUPAL_NO_CACHE
   );  
   return $blocks;
 }

 /**
  * Implements hook_block_view().
  */
 function trivia_block_view($delta = '') {
   $block = array();
   switch ($delta) {
     case 'logo':
        $block['subject'] = t('Logo Subtheme @boostrap');
        $logo = array(
          'path' => theme_get_setting('logo', 'trivia'), 
          'alt' => t('Logo'),
          'title' => t('Trivia Game'),
          'attributes' => array('class' => 'logo-img', 'id' => 'logo-img'),
       );
       $block['content'] =  theme('image', $logo);
       break;
     case 'time':
        $node = node_load(arg(1));
        if ($node->time_limit != FALSE) {
            drupal_add_js(drupal_get_path('module', 'trivia') . '/js/' . 'time.js');
            $node = node_load(arg(1));
            drupal_add_js(array('trivia' => array('fulltimequiz' => $node->time_limit)), array('type' => 'setting'));
            $clock = array(
                'path' => 'sites/all/themes/custom/trivia/img/gif/reloj_negro.gif', 
                'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
            );
            $block['subject'] = theme('image', $clock);
            $render = array(
              '#prefix' => '<div class="progress">',
              '#markup' => '<div class="progress-bar progress-bar-info progress-bar-striped active"></div>',
              '#suffix' => '</div>', 
            ); 
            $block['content'] = render($render);
        }
       break;
   }
   return $block;
 }