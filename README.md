# cy-wire

Ce programme sert à faire la synthèse des données d'un système de distribution d'électricité, à partir d'un fichier .csv de la forme:

|Power plant|HV-B Station|HV-A Station|LV Station|Company|Individual|Capacity|Load|
|-----------|------------|------------|----------|-------|----------|--------|----|

### NOM
`cy-wire`
### SYNOPSIS

```sh
./cy-wire.sh [fichier] [type de station] [type de consommateur] [numéro de centrale]
```

### DESCRIPTION

**[fichier]**

Le chemin vers le fichier .csv contenant les données d'entrée.

**[type de station]**

Correspond au type de station utilisée par le programme.

Valeurs possibles: `hva`, `hvb` ou `lv`.

**[type de consommateur]**

Spécifie le type de consommateur: les particuliers, les entreprises ou les deux.

Valeurs possibles: `all`, `indiv` ou `comp`.

**[numéro de centrale]**

Correspond à l'identifiant de la centrale mère des options précédentes. 

Valeurs possibles: `[1:5]`, `all`.


### ATTENTION

Les options suivantes sont interdites car seulement des entreprises sont connectées aux stations HV-B et HV-A:

```
hvb all
hvb indiv
hva all
hva indiv
```
