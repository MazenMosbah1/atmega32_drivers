#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char		u8;
typedef unsigned short int	u16;
typedef unsigned long int	u32;
typedef unsigned long long	u64;

typedef signed char			s8;
typedef signed short int	s16;
typedef signed long int		s32;
typedef signed long long	s64;

typedef float		f32;
typedef double		f64;
typedef enum{FALSE = 0, TRUE}Bool_t;
	
#define NULLPTR		((void*)0)


#endif /* STDTYPES_H_ */