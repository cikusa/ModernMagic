local sounds={'alert','bonus','bonus2','cancel00','cardget','cat00','cat01','ch00','ch01',
		'damage00','damage01','enep00','enep01','enep02','extend','graze','gun00',
		'hint00','invalid','item00','kira00','kira01','kira02','lazer00','lazer01',
		'msl','nep00','ok00','option','pause','pldead00','plst00','power0','power1',
		'powerup','select00','slash','tan00','tan01','tan02','timeout','timeout2',
		'warpl','warpr','water','explode'}
for _,v in pairs(sounds) do
	LoadSound(v,'THlib\\se\\se_'..v..'.wav')
end