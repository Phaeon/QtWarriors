<?php

use Framework\Controleur;

class ControleurModelisation extends Controleur {

    public function __construct() {
    }
    
    public function index() {   
        $this->genererVue();
    }

    public function troisDimention() {   
        $this->genererVue();
    }

    public function application() {   
        $this->genererVue();
    }

}

