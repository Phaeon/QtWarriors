<?php

use Framework\Controleur;

class ControleurDL extends Controleur {

    public function __construct() {
    }

    public function index() {   
        $this->genererVue();
    }

}

