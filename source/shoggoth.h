typedef struct point2D point2D;
typedef struct objHandle objHandle;
typedef struct token token;

struct point2D
{
	float			_xf;
	float			_yf;

	int				_x;
	int				_y;
};

struct objHandle
{
	int				_pointer;
	int				_spriteIndex;
	// int			
};

struct token {
	point2D			_pos;
	void			(*_script)(token*);
};


void newToken();
token gameStack[16];