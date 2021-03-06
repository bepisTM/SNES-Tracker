.include "cpu/memorymap.i"

.define UnderlineTileNum 3

.BANK 0
.orga $8000
.section "underline" SEMIFREE

ClearUnderlineLocations:
	php
	rep #$30
	phd
	
	lda #String1.w
	tcd
	lda ($00)
	ldy #5
	pha
	and #$ff00
	lsr
	lsr
	lsr
	; that's the equiv. of 5 shifts left from LSB;
	sta temp.w
	pla
	and #$00ff
	clc
	adc temp.w
	; word address to byte address << 1
	asl
	tax
	lda #0.w
-	sta bg2copy.l,X
	inx
	inx
	dey
	bne -
	
	
	lda #String2.w
	tcd
	lda ($00)
	ldy #9
	
	pha
	and #$ff00
	lsr
	lsr
	lsr
	; that's the equiv. of 5 shifts left from LSB;
	sta temp.w
	pla
	and #$00ff
	clc
	adc temp.w
	; word address to byte address << 1
	asl
	tax
	lda #0.w
-	sta bg2copy.l,X
	inx
	inx
	dey
	bne -
	
	lda #String3.w
	tcd
	lda ($00)
	ldy #9
	pha
	and #$ff00
	lsr
	lsr
	lsr
	; that's the equiv. of 5 shifts left from LSB;
	sta temp.w
	pla
	and #$00ff
	clc
	adc temp.w
	; word address to byte address << 1
	asl
	tax
	and #0.w
-	sta bg2copy.l,X
	inx
	inx
	dey
	bne -

	
	pld
	
	plp
	rts

; call with X/Y coord in A 16 bit
; A = YX
; Y = quanity
DisplayUnderline:
;expect rep #$30
.accu 16
.index 16
	php
	pha
	and #$ff00
	lsr
	lsr
	lsr
	; that's the equiv. of 5 shifts left from LSB;
	sta temp.w
	pla
	and #$00ff
	clc
	adc temp.w
	; word address to byte address << 1
	asl
	tax
	sep #$20
-	lda #UnderlineTileNum
	sta bg2copy.l,X
	lda #%00000100
	sta bg2copy.l+1,X
	inx
	inx
	dey
	bne -
	plp
	rts	
	
UploadUnderline:
	php
	rep #$10
	sep #$20
	lda #$80
	sta $2115
	ldx #$4000+($10*UnderlineTileNum)
	stx $2116
	rep #$20
	ldx #0
-	lda Underline.w,X
	sta $2118
	inx
	inx
	cpx #$20
	bne -
	plp
	rts
;4bpp
Underline:
	.db 00,00,00,00,00,00,00,00
	.db 00,00,00,00,00,00,00,$FF
	.db 00,00,00,00,00,00,00,00
	.db 00,00,00,00,00,00,00,00


.ends