
#ifndef UTILS_H_
#define UTILS_H_


#define SET_BIT(reg,bit)						(reg=reg|(1 << bit))
#define CLEAR_BIT(reg,bit)						(reg=reg&(~(1 << bit)))
#define READ_BIT(reg,bit)						((reg>>bit)&1)
#define TOGGLE_BIT(reg,bit)						(reg=reg^(1 << bit))
#define writebit(reg, bit, value)				(reg = reg&(~(1 << bit)) | (value << bit))
#define CHECK_IF_BIT_SET(REG , BIT)				(REG & (1<<(BIT)))
#define CHECK_IF_BIT_CLEARED(REG , BIT)			(!(REG & (1<<(BIT))))
#define CHECK_IF_BIT_SET_MODIFIED(REG , BIT)	(1 &(REG>>(BIT)))
#define CHECK_IF_BIT_CLEARED_MODIFIED(REG,BIT)	(!(1 &(REG>>(BIT))))


#endif /* UTILS_H_ */