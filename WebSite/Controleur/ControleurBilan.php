<?php

use Framework\Controleur;

class ControleurBilan extends Controleur {

    public function __construct() {
    }

    public function index() {   
        $this->genererVue();
    }

}

