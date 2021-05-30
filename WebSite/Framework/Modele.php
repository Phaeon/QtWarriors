<?php
namespace Framework;

use PDO;
//require_once 'Configuration.php';

abstract class Modele {

    private static $bdd;

    protected function executerRequete($sql, $params = null) {
        if ($params == null) {
            $resultat = self::getBdd()->query($sql);
        }
        else {
            $resultat = self::getBdd()->prepare($sql);
            $resultat->execute($params);
        }
        return $resultat;
    }

    private static function getBdd() {
        if (self::$bdd === null) {
            $dsn = Configuration::get("dsn");
            $login = Configuration::get("login");
            $mdp = Configuration::get("mdp");

            self::$bdd = new PDO($dsn, $login, $mdp, 
                    array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION));
        }
        return self::$bdd;
    }

}
