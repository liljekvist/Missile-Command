# DV1627 Projekt: Missile Command

## Vad ska du göra?

I detta projekt ska du tillämpa innehållet i kursen och strukturera en egen problemlösning med klasser och objekt. Din uppgift är att implementera en simpel version av spelet Missile Command, och skriva en kort rapport där du beskriver hur du löst problemet och uppfyller projektet kriterier. Innan du läser vidare kan du provspela en fullskalig version av spelet här:

https://games.aarp.org/games/atari-missile-command (varning: hög volym)

Din implementation kommer vara en nerskalad version av spelet. Projektuppgiften betygsätts från A-F. Genom att implementera en simpel version av spelet enligt givna kriterier, samt ger svar på efterfrågade punkter i din rapport, så når du betyget E. För ett högre betyg behöver du lösa fler problem.

Efter denna nivå finns det ett fyra olika extraval som bygger vidare på grundspelet, där varje extraval har egna kriterier som måste uppfyllas. Varje extraval du implementerar, och uppfyller kritierer för, ökar ditt betyg med en nivå. Det finns ingen ordning på dessa extraval, du får blanda dessa fritt i vilken ordning du själv är bekväm med. Se följande lista för betygsättning:

- Betyg E: grundspel + rapport
- Betyg D: grundspel + rapport + 1 extraval
- Betyg C: grundspel + rapport + 2 extraval
- Betyg B: grundspel + rapport + 3 extraval
- Betyg A: grundspel + rapport + 4 extraval

Notera att ett extraval måste vara fulltständigt implementerat enligt dess kriterier för att uppnå sin poäng. Halvfärdiga, eller "nästan färdiga", lösningar räknas ej.

## Betygskriterier

**Kodkriterier:**
- Inga minnesläckor.
- Inga uppenbara kraschar.
- Kod ska vara skriven på engelska och vara tydlig att läsa och förstå.
- En objketorienterad lösning med arv och polymorfism ska användas.
- Det är tillåtet att använda allt från standardbiblioteket (`std`)
    - Detta inkluderar exempelvis `vector`, smartpekare etc.

**För betyget E:**
- [X] Det måste finnas en egenskapad klass **Tower** som används i spelet.
	- Det ska bara finnas ett torn som kan skjuta missiler.
    - Det ska finnas någon form av "nerkylning" (cooldown) för att avfyra missiler. Exempelvis kan det finnas en begränsning på en (1) sekund innan en missil kan avfyras igen. Det kan alltså hända att spelaren väljer att avfyra en missil, men inget händer eftersom tornet "kyler ner".
- [X] Det måste finnas en egenskapad abstrakt basklass **Projectile** som projektiltyper ärver från.
- [X] Det måste finnas en egenskapad klass **Missile** som ärver från **Projectile** och används i spelet.
	- När spelaren trycker ner vänster musknapp ska tornet skjuta en missil till musens position i fönstret.
	- Missiler är visuella projektiler som färdas i en rak linje till sin destination.
	- När en missil når sin destination ska den "försvinna". Det är dock okej (och rekommenderat) att "återanvända" missilen igen istället för att avallokera och skapa nya.
	- När en missil når sin destination ska alla meteoriter inom en mindre radie också förstöras.
- [X] Det måste finnas en egenskapad klass **Meteorite** som ärver från **Projectile** och används i spelet.
	- Meteroriter ska färdas från himlen ner mot marken i en rak linje. Linjen som meteoriter färdas ska ha slumpmässig riktning mot marken. De ska alltså inte bara falla "rakt ner".
	- När en meteorit når marken ska den "försvinna" och spelaren tappar ett av sina kvarvarande liv. Likt missiler är det okej (och rekommenderat) att "återanvända" meteoriter istället för att avallokera och skapa nya. 
- [X] Det ska vara finnas en visuell skillnad mellan olika objekt som ritas i spelet.
    - Det ska vara tydligt att se skillnad mellan torn, missiler och meteoriter.
    - Grafiken behöver inte vara "snygg". Det är ok att använda simpla former och färger för att rita spelet.
    - Det finns inga krav på "animationer". Tornet måste alltså inte "sikta", utan kan vara en fast kvadrat längst ner i fönstret.
- [X] Det ska finnas en array/behållare där samtliga pekare (av samma basklasstyp) till missiler och projektiler ska samlas.
    - Alla missiler och projekter ska allokeras på heapen, och pekare till dessa objekt ska alltså blandas i en och samma array/behållare.
    - Det är tillåtet att använda en behållare från standardbiblioteket för detta, exempelvis `std::vector`.
    - Polymorfism ska användas i någon form.
- [ ] Spelaren börjar med tre (3) liv. Spelet fortsätter tills att spelaren har 0 liv och förlorar, dvs. när tre olika meteorieter har nått marken. Spelarens uppgift är alltså att förstöra meteoriter innan de når marken för att fortsätta spela. Spelarens kvarvarande liv ska visualiseras på något vis, exempelvis genom att rita tre symboler eller en siffra i hörnet av fönstret.
- [ ] Spelet kan påbörjas direkt programmet startar. När spelet är över ska spelaren presenteras med texten "Game Over" följt av att programmet kan avslutas.

**Extraval för högre betyg:**
- [ ] **Meny**
    - Ska presenteras för spelaren när programmet startar, och återgås till när spelet är över.
    - Det ska inte finnas någon gräns för hur många gånger spelet kan startas från menyn och återgå tillbaka. Rekursion är alltså **inte** ok här.
    - Det ska *åtminstone* finnas två val för spelaren att välja mellan i menyn: starta spelet och avsluta.
- [X] **Fler torn**
    - Det ska finnas tre (3) torn istället för ett (1).
    - När spelaren väljer att avfyra en missil ska denna avfyras från närmsta torn (till destinationen) som inte är på "nerkylning" (cooldown). Om samtliga torn är på "nerkylning" kan ingen missil skjutas.
- [ ] **Spelrundor**
    - Istället för ett kontinuerligt spel som bara tar slut när spelaren förlorar ska det finnas "spelrundor".
    - Under en spelrunda ska det skapas ett bestämt antal meteoriter.
    - Spelaren vinner en spelrunda när alla meteoriter i den rundan är förstörda.
    - Det ska finnas någon tydlig indikation att en ny spelrunda påbörjas, exempelvis en viss text i fönstret.
    - Antalet meteoriter ska öka för varje spelrunda. Exempelvis kan första rundan innehålla fem (5) meteoriter, andra rundan tio (10) meteoriter, tredje rundan femton (15) meteoriter osv.
- [ ] **Highscores**
    - Spelaren ska samla någon form av poäng under sitt spelande. Exempelvis kan spelaren få poäng baserat på speltid, eller antalet meteoriter som spelaren förstör.
    - Under speltid ska spelaren alltid se sin nuvarande poäng. Exempelvis kan poängen ritas som siffra i ett av hörnen på fönstret.
    - Upp till fem (5) högsta poängresultat ska lagras till en fil mellan programkörningar. Poängen i filen ska lagras i ordning.
    - När spelet är över ska spelarens poäng jämföras med de tidigare högsta poängresultaten i den sparade filen, och skrivas in i filen om nuvarande poäng är del av de fem högsta poängresultaten. Detta kan innebära att om det redan finns fem (5) resultat sen tidigare ska nuvarande poäng skriva över en av dessa.
    - När spelet är över ska resulterande poäng presenteras för spelaren, samt den uppdaterade listan av de fem (5) högsta poängen. 
    - Det är tillåtet, men inget krav, att spelaren ska skriva sitt namn för sin poäng.

**Vad rapporten ska innehålla**

Rapporten ska vara renskriven på antingen svenska eller engelska. Renskriven innebär att du ska läsa igenom och åtgärda språk- och stavfel. Använd gärna program som Microsoft Word eller Google Docs som hjälper dig med detta.

Det finns ingen strikt gräns för antal ord i rapporten, men följande punkter ska ingå belysas: 

1. Vilket betyg du strävar efter med vad du implementerat.
2. Ett klassdiagram som visar en överblick av dina klasser i programmet.
    - Klassnamn och relationer ska presenteras.
    - Viktiga funktioner och variabler i klasser ska presenteras. Du behöver inte visa alla funktioner och variabler i klasser. Exempel på viktiga funktioner kan vara `Update` eller `Draw`.
3. Förklara hur du uppfyllt kraven för det betyg du strävar efter.
    - I din motivation ska det tydligt framgå att du uppfyller samtliga kriterier för betyget.
4. Argumentera för- och nackdelar med din implementation.
    - Vad har du lärt dig på vägen?
    - Vad hade du gjort annorlunda om du skulle göra om projektet idag?

## Tips

- Skapa en abstrakt basklass `SceneObject` som alla spelobjekt ärver från, exempelvis torn och projektiler.
    - Detta gör det möjligt att hantera alla scenobjekt med polymorfism. Exempelvis kan denna klass ha de (rent) virtuella funktionerna `Update` och `Draw` (från `sf::Drawable`) som alla scenobjekt kan välja att överskugga.
    - Notera att det finns ett kriterie som säger att alla projektiler ska lagras i samma array/behållare, och detta uppfyller kriteriet. Det finns inget som hindrar fler typer av scenobjekt att finnas i samma samling. :)
- Skapa en behållarklass `Scene` som hanterar lagrar alla scenobjekt.
    - Detta gör ett lättare hantera alla scenobjekt. Exempelvis kan scenen ha en funktion `Update` som i sig itererar och kallar på `Update` för samtliga scenobjekt.
