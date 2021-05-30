<?php

use Framework\Controleur;

class ControleurIA extends Controleur {

    public function __construct() {
    }

    public function index() {   
        $this->genererVue();
    }

    public function alphaBeta(){
        $this->genererVue();
    }

    public function automates(){
        $this->genererVue();
    }

}

