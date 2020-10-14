# Assignment 1 : Brutto-Netto Rechner

## Lernziel
Datentypen, Operatoren, Casts, Kontrollstrukturen, Ein-/Ausgabe, Funktionen

## Aufgabenstellung
Schreiben Sie ein Programm, das ausgehend von einem Bruttoentgelt
 * den Sozialversicherungsbeitrag,
 * die Lohnsteuer und
 * das Nettoentgelt

ausrechnet.
Aufgrund vieler Details in der Berechnung des Nettoentgelts in Österreich (viele Leistungsklassen, Absetzbeträge, Werbungskosten, rückwirkende Steuernovelle, etc.), wird in diesem Übungsbeispiel ein vereinfachter Brutto-Netto-Rechner erstellt. Interessierte können sich gerne [eine Zusammenfassung über die tatsächliche Berechnung des Nettoentgelts in Österreich](https://www.lernenwillmehr.at/wp-content/uploads/2020/01/Lernen-Will-Mehr_aktuelles-Personalverrechnung_2020.pdf) ansehen – für dieses Assignment ist dieses Detailwissen aber nicht erforderlich.

In diesem Assignment wird das Nettoentgelt mit der Formel
```math
\text{Nettoentgelt} = \text{Bruttoentgelt} - \text{Sozialversicherungsbeitrag} - \text{Lohnsteuer}
```
berechnet.

Wie Sozialversicherungsbeitrag und Lohnsteuer zu berechnen sind, ist in den Abschnitten [Sozialversicherungsbeitrag](#berechnung-des-sozialversicherungsbeitrags-sv) und [Lohnsteuer](#berechnung-der-lohnsteuer-lst) beschrieben. Die folgenden Abschnitte zeigen auch, wie die
Ausgaben des Programms auszusehen haben.

---
**ACHTUNG!**

Bitte befolgen Sie die Anweisungen zur Ausgabe *genau*, da selbst bei kleinen Fehlern (z.B. ein Leerzeichen
zu wenig oder zu viel) die Test Cases fehlschlagen! Das wäre sehr schade und deshalb stellen wir Ihnen in
diesem Repository auch ein Testsystem zur Verfügung. Nutzen Sie es unbedingt! Es gibt Ihnen wertvolle
Hinweise auf Fehler in Ihrem Programm.

---

### Eingabe des Bruttoentgelts
Im ersten Schritt wird die/der Benutzer\*in zu einer Eingabe aufgefordert. Eine valide Eingabe ist eine Ganzzahl größer als 0 und ≤ 5 Millionen. Diese Ganzzahl gibt das Bruttoentgelt an.
```
Ihr monatliches Bruttoeinkommen: <wert>
```
Dabei wird `<wert>` durch die (mit Enter abgeschlossene) Benutzereingabe ersetzt. Die spitzen Klammern sind *nicht* Teil der Benutzereingabe. Unsere [Beispielausgabe](#beispielausgabe) verdeutlicht, wie die Ausgabe auszusehen hat.

Sollte die Eingabe nicht valide sein, erscheint folgende Fehlermeldung:
```
Invalide Eingabe!\n
```
Die hier abgebildeten Zeichen `\` und `n` sind nicht als einzelne Zeichen auszugeben, sondern sind als Newline-Character (`\n`) zu verstehen.

Nach der Fehlermeldung startet das Program von vorne, das heißt es verlangt wieder nach einer Eingabe (so lange, bis die Eingabe valide ist).
(Tipp: Bei den Test Cases wird nur auf einzelne Ganzzahlen getestet, Sie müssen sich also keine Gedanken darüber machen, wie das Programm mit anderen Eingaben (z.B. Buchstaben) umgehen soll.)

### Berechnung des Sozialversicherungsbeitrags (SV)
#### Sozialversicherungsbeitrag bei einem Bruttoentgelt bis (inkl.) 5370 €
Der Sozialversicherungsbeitrag lässt sich aus der Beitragsgrundlage (=monatliches Bruttoentgelt) errechnen. Bis zu einer Beitragsgrundlage von 5370 € lautet die Formel dafür

```math
\text{Sozialversicherungsbeitrag} = \text{Beitragsgrundlage} \cdot \frac{\text{Beitragssatz}}{100},
```

wobei der (von der Beitragsgrundlage abhängige) Beitragssatz der folgenden Tabelle entnommen werden kann.

| Beitragsgrundlage	€ | Beitragssatz % |
| --------- | :------: |
| 1 - 460 | 0 |
| 461 - 1733 | 15 |
| 1734 - 1891 | 16 |
| 1892 - 2049 | 17 |
| 2050 - 5370 | 18 |

Die Geringfügigkeitsgrenze liegt demnach bei 460 €. Das heißt, wer 460 € oder weniger verdient, zahlt keine Sozialversicherung.

#### Sozialversicherungsbeitragbeitrag bei einem Bruttoentgelt über 5370 €
Die Höchstbeitragsgrundlage liegt bei 5370 €. Das heißt, wer mehr verdient, zahlt gleich viel wie jemand, der 5370 € verdient.

### Berechnung der Lohnsteuer (LSt)
Eigentlich werden im österreichischen Einkommensteuergesetz (EStG) Lohnsteuerklassen (Tarifstufen) in Abhängigkeit vom Jahreseinkommen definiert. Der Einfachheit halber rechnen wir aber mit monatlichen Bezügen. Die Beitragsgrundlage für die LSt ist das monatliche Bruttoentgelt **nach Abzug der Sozialversicherung**. (Das bedeutet auch, dass sich die Beitragsgrundlage für die SV und jene für die LSt unterscheiden können!)

Auch bei der LSt gibt es eine Tabelle, mit deren Hilfe der zu zahlende Betrag ermittelt werden kann. Die Berechnung erfolgt aber etwas anders als bei der SV.

| Beitragsgrundlage	€ | Beitragssatz % |
| --------- | :------: |
| 0,01 - 1000,00	| 0 |
| 1000,01 - 1500,00 | 20 |
| 1500,01 - 2500,00 | 30 |
| 2500,01 - 5000,00 | 40 |
| \> 5000,00 | 50 |

Im Gegensatz zur SV wird bei der LSt nicht die gesamte Beitragsgrundlage mit dem höchsten erreichten Beitragssatz multipliziert. Es werden stattdessen die einzelnen Teile der Beitragsgrundlage mit dem jeweiligen Beitragssatz multipliziert. Für die ersten 1000€ werden 0% berechnet; für die nächsten 500€ sind es 20%; für die nächsten 1000€ 30% usw. (siehe Tabelle oben). Alle so ermittelten Werte werden addiert.

Die Formel für die Berechnung der LSt lautet: 

```math
\text{Lohnsteuer} = \text{Teil 1 der Beitragsgrundlage} \cdot \frac{\text{Beitragssatz}_1}{100} \\
                    + \text{Teil 2 der Beitragsgrundlage} \cdot \frac{\text{Beitragssatz}_2}{100} \\
                    + ...
```

---
**Beispiel:**

Die Beitragsgrundlage für die LSt sei 2605 €. Dann beträgt die LSt
$`1000 \cdot \frac{0}{100} + 500 \cdot \frac{20}{100} + 1000 \cdot \frac{30}{100} + 105 \cdot \frac{40}{100}`$ €.

---

Der gezeigte Rechenweg ergibt lediglich die *vorläufige* LSt. Die tatsächliche LSt kann von der vorläufigen LSt abweichen, wenn die/der Benutzer\*in Kinder hat.
Vor der Berechnung der tatsächlichen Lohnsteuer wird die/der Benutzer\*in gefragt, ob dies der Fall ist.
```
Kinder im Haushalt?: <Jj/Nn>
```
Dabei wird `<Jj/Nn>` durch die (mit Enter abgeschlossene) Benutzereingabe ersetzt. Sowohl
Groß- ("J"/"N") als auch Kleinschreibung ("j"/"n") sind erlaubt.

Sollte die Eingabe kein erlaubter Wert sein, erscheint folgende Fehlermeldung:
```
Invalide Eingabe!\n
```
Nach der Fehlermeldung fährt das Programm wieder mit der Frage nach den Kindern fort.
(Tipp: Bei den Test Cases wird auf einzelne alphanumerische Zeichen getestet.)

Wenn die/der Benutzer\*in steuerpflichtig ist und Kinder hat, sinkt die Lohnsteuer um bis zu 100 € (sie kann jedoch nicht negativ werden). Genauer gesagt,
 - ist die vorläufige LSt ohne Kinder $`\geq 100`$ €, so ist die tatsächliche LSt mit Kindern um 100 € geringer und
 - ist die vorläufige LSt ohne Kinder $`< 100`$ €, so ist die tatsächliche LSt mit Kindern gleich 0.

### Ausgabe
Nachdem alle oben beschriebenen Eingaben getätigt wurden, gibt das Programm eine
Übersicht über die Berechnungen aus.
```
Brutto:\t\t<wert_br>\n
SV:\t\t<wert_sv>\n
LSt:\t\t<wert_ls>\n
Netto:\t\t<wert_ne>\n
```
Dabei werden die Platzhalter `<wert_XX>` durch die entsprechenden berechneten Werte ersetzt. Beachten Sie bitte folgende Hinweise:
* Alle Beträge werden auf 2 Nachkommastellen genau angezeigt.
* Alle Beträge haben eine Feldbreite von 12.
* `<wert_sv>` und `<wert_ls>` werden mit einem Vorzeichen angezeigt.
* Beachten Sie die Tabulatorzeichen `\t`.
* Es werden keine Leerzeichen oder das Minuszeichen benutzt.

Hilfestellung zu Formatierungsoptionen finden Sie unter [Wikibooks](https://de.wikibooks.org/wiki/C-Programmierung:_Einfache_Ein-_und_Ausgabe) und [printf-Cheatsheet](https://kuepper.userweb.mwn.de/informatik/printf.pdf).

## Beispielberechnung
```
Brutto =                1880 €
SV 16% =                -300,80 €
Brutto-SV =             1579,20 €
LS (1500-1000)*20% +
   (1579,20-1500)*30% =  123,76 €
Kind J LS-100€ =         -23,76 €
Netto =                 1555,44 €
```

## Beispielausgabe
```
Ihr monatliches Bruttoeinkommen: 2400
Kinder im Haushalt?: m
Invalide Eingabe!
Kinder im Haushalt?: n
Brutto:		     2400.00
SV:		     -432.00
LSt:		     -240.40
Netto:		     1727.60

```

## Spezifikation
* Die Eingabe des Bruttoentgelts muss im Datentyp Integer (int) erfolgen.
* abzugebende Datei: a1.c
* Abgabe bis *spätestens*: 07.11.2020 23:59 (in Österreich gültige Zeit)

## Bewertung
Das Assignment wird [wie im TeachCenter beschrieben](https://tc.tugraz.at/main/mod/page/view.php?id=55761) bewertet. Machen Sie sich auch mit dem [Beurteilungsschema](https://tc.tugraz.at/main/mod/page/view.php?id=55602) für die Übungen vertraut, insbesondere mit den Regeln zu Plagiaten!

---
**ACHTUNG!**

Damit die Abgabe als ernsthafter Versuch gewertet wird, muss das abgegebene Programm
mindestens **4** Test Cases bestehen!

---
