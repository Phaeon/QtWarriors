<?php

use Framework\Controleur;

class ControleurAccueil extends Controleur {

    public function __construct() {
    }

    public function index() {   
        $this->genererVue();
    }

}

