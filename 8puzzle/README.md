Semestrální práce z KIV/UIR 2012
================================

Zadání:
-------

V programovacím jazyce C zpracujte jednoduchý výukový program, který plně
demonstruje nalezení řešení následující úlohy: Jde o převedení hlavolamu "8"
(při respektování pořadí aplikace produkčních pravidel uvedeného na přednášce)
metodou prohledávání grafu s využitím heuristické funkce.

    f(n_i) = g(n_i) + h(n_i),
    g(n_i) = d(n_i)            (délka cesty z n_0 do n_i)
    h(n_i) = P(n_i) + 3 Q(n_i), kde

+ P(n_i) je součet vzdáleností každého kamene hlavolamu od svého cílového místa
(v možných posuvech).
+ Q(n_i) je míra porušení pořadí kamenů zahrnuta tak, že
    + přičítáme hodnotu 2 za každý kámen nenacházející se ve středu pole a jenž
není následován správným kamenem, 
    + za kámen ve středu pole přičítáme 1.
