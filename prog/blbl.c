if (collision(spritePosition,plateformePos[i])==1){
	    if (plat_array[i] < 3) {
	      spritePosition.x = plateformePos[i].x - SPRITE_SIZE ;
	    }
	    if (plat_array[i] == 3) {
	      if (clef >= 1) {
		clef -= 1;
		plat_array[i] = 0;
	      }
	      else {
		spritePosition.x = plateformePos[i].x - SPRITE_SIZE ;
	      }
	    }
	    if (plat_array[i] == 4) {
	      plat_array[i] = 0;
	      if (item == 1) {
		vie += 1;
		tempsItem = 0;
	      }
	      else {
		vie += 1;
		item = 1;
	      }
	    }
	    if (plat_array[i] == 5) {
	      plat_array[i] = 0;
	      if (item == 2) {
		clef += 1;
		tempsItem = 0;
	      }
	      else {
		clef += 1;
		item = 2;
	      }
	    }
	  }