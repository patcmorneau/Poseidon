PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//841727/154315/2.46/2/3/Capacitor Polarised

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c225_h150"
		(holeDiam 1.5)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 2.25) (shapeHeight 2.25))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 2.25) (shapeHeight 2.25))
	)
	(padStyleDef "s225_h150"
		(holeDiam 1.5)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 2.25) (shapeHeight 2.25))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 2.25) (shapeHeight 2.25))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "CAPPRD500W130D2150H800" (originalName "CAPPRD500W130D2150H800")
		(multiLayer
			(pad (padNum 1) (padStyleRef s225_h150) (pt 0, 0) (rotation 90))
			(pad (padNum 2) (padStyleRef c225_h150) (pt 5, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(arc (pt 2.5, 0) (radius 0) (width 0.05))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 2.5, 0) (radius 0) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 2.5, 0) (radius 0) (width 0.025))
		)
	)
	(symbolDef "DB-5R5D105T" (originalName "DB-5R5D105T")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 100 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 0 mils -35 mils) (rotation 0]) (justify "UpperLeft") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 500 mils 0 mils) (rotation 180) (pinLength 100 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 500 mils -35 mils) (rotation 0]) (justify "UpperRight") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 200 mils -100 mils) (width 6 mils))
		(line (pt 200 mils -100 mils) (pt 230 mils -100 mils) (width 6 mils))
		(line (pt 230 mils -100 mils) (pt 230 mils 100 mils) (width 6 mils))
		(line (pt 230 mils 100 mils) (pt 200 mils 100 mils) (width 6 mils))
		(line (pt 180 mils 50 mils) (pt 140 mils 50 mils) (width 6 mils))
		(line (pt 160 mils 70 mils) (pt 160 mils 30 mils) (width 6 mils))
		(line (pt 100 mils 0 mils) (pt 200 mils 0 mils) (width 6 mils))
		(line (pt 300 mils 0 mils) (pt 400 mils 0 mils) (width 6 mils))
		(poly (pt 300 mils 100 mils) (pt 300 mils -100 mils) (pt 270 mils -100 mils) (pt 270 mils 100 mils) (pt 300 mils 100 mils) (width 10  mils))
		(attr "RefDes" "RefDes" (pt 350 mils 250 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 350 mils 150 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "DB-5R5D105T" (originalName "DB-5R5D105T") (compHeader (numPins 2) (numParts 1) (refDesPrefix C)
		)
		(compPin "1" (pinName "+") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "-") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "DB-5R5D105T"))
		(attachedPattern (patternNum 1) (patternName "CAPPRD500W130D2150H800")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Manufacturer_Name" "Elna")
		(attr "Manufacturer_Part_Number" "DB-5R5D105T")
		(attr "Mouser Part Number" "555-DB-5R5D105T")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Elna/DB-5R5D105T?qs=r8OyiFxb6Rcu1BWmqcONIQ%3D%3D")
		(attr "RS Part Number" "")
		(attr "RS Price/Stock" "")
		(attr "Description" "Supercapacitors / Ultracapacitors MEM CAP 5.5V 1.0F")
		(attr "<Hyperlink>" "http://www.mouser.com/datasheet/2/129/DB_DBNe-3084.pdf")
		(attr "<Component Height>" "8")
		(attr "<STEP Filename>" "DB-5R5D105T.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
