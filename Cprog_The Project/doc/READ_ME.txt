Nicole Nechita Grupp 07

I spelet man är en flyplan som flyger i rymden. Genom att flytta på muset, flygplanet följer detta. Löpande skapas fiender som försöker kollidera med denna flygplan. Spelaren måste undvika dem så långt som möjligt. Efter antal liv blir 0 då får man inte punkt längre och liv går inte ner längre. Men, när som helst, det går att omstarta tillståndet av spelaren i spelet igenom en tangentbord händelse. Man börjar om med full liv och 0 poäng. Och dett kan göras när som helst.

CONTROLS: KONTROLL
Move Mouse(Flytta musen) =  Move Airplane | Flytta flygplan
Any Key =  -Restart player state | Omstarta spelare tillstånd

Alla texture, audio, font måste finnas i /resources mappen i respektiva mappar beroende på typ av fil. Detta hanteras med constants::getResPath. som är den relativa path till resources mappen.

Om en objekt skapas då det behöver en textur och en referense till session. Session skapas i main. Ljud behöver inte läggas men det bidrar positiv till spelet. Efter run() anropet slutas ta bort Enemy och Bullet textur om dem används. Härefter man påverkar vilken spel spelmotorn skapar med hjälp av funktioner som lägger ljud, lägger textur, eller byter på attribut.

Alla spelobjekt skapas på heapen och får bara skapas med hjälp av getInstance() funktion.

Man kan testa tillämplingen som finns i main genom att skriva "make" sedan "./build/debug/play.exe" i terminalen