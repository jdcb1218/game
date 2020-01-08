<?php drupal_add_js(drupal_get_path('module', 'trivia') . '/js/' . 'count.js'); ?>
<div id="container-count">
	<div class="get-ready-to-play">
		<?php print(t('Get ready to play')); ?>
	</div>
	<div class="we-start">
		<?php print(t('We start in:')); ?>
		<div id="count-list"></div>
	</div>
</div>