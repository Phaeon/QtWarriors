<?php
namespace Framework;
use Exception;
class Configuration {

    private static $parametres;

    public static function get($nom, $valeurParDefaut = null) {
        if (isset(self::getParametres()[$nom])) {
            $valeur = self::getParametres()[$nom];
        }
        else {
            $valeur = $valeurParDefaut;
        }
        return $valeur;
    }

    private static function getParametres() {
        if (self::$parametres == null) {
            $cheminFichier = "Config/dev.ini";
            if (!file_exists($cheminFichier)) {
                $cheminFichier = "Config/prod.ini";
            }
            if (!file_exists($cheminFichier)) {
                throw new Exception("Aucun fichier de configuration trouvé");
            }
            else {
                self::$parametres = parse_ini_file($cheminFichier);
            }
        }
        return self::$parametres;
    }

}

