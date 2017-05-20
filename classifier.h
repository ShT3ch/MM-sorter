#define	           blue	 0
#define	          green	 1
#define	         orange	 2
#define	            red	 3
#define	          white	 4
#define	         yellow	 5

float check_if_it_is_blue_object(float r, float g, float b, float c)
    {
        return -1.02145307572 + (((float)r - 48569.2)/10044.1032731)*(-0.404742464935) 
		+ (((float)g - 38272.4)/5813.49153607)*(-0.188908221395) 
		+ (((float)b - 45261.36)/7281.40957167)*(0.996041661019) 
		+ (((float)c - 133028.24)/16919.8930523)*(0.184730201129);
    }

float check_if_it_is_green_object(float r, float g, float b, float c)
    {
        return -1.87139225576 + (((float)r - 48569.2)/10044.1032731)*(-1.96081617853) 
		+ (((float)g - 38272.4)/5813.49153607)*(3.85329773683) 
		+ (((float)b - 45261.36)/7281.40957167)*(-0.996406432214) 
		+ (((float)c - 133028.24)/16919.8930523)*(-1.62411197377);
    }

float check_if_it_is_orange_object(float r, float g, float b, float c)
    {
        return -2.44155462589 + (((float)r - 48569.2)/10044.1032731)*(2.43327865833) 
		+ (((float)g - 38272.4)/5813.49153607)*(-2.08198780451) 
		+ (((float)b - 45261.36)/7281.40957167)*(0.277068188203) 
		+ (((float)c - 133028.24)/16919.8930523)*(0.787528133858);
    }

float check_if_it_is_red_object(float r, float g, float b, float c)
    {
        return -2.08618774142 + (((float)r - 48569.2)/10044.1032731)*(1.67598531891) 
		+ (((float)g - 38272.4)/5813.49153607)*(-3.40039138834) 
		+ (((float)b - 45261.36)/7281.40957167)*(2.28610402631) 
		+ (((float)c - 133028.24)/16919.8930523)*(-0.648566827851);
    }

float check_if_it_is_white_object(float r, float g, float b, float c)
    {
        return -2.9265389812 + (((float)r - 48569.2)/10044.1032731)*(-1.98360981395) 
		+ (((float)g - 38272.4)/5813.49153607)*(0.0368583789583) 
		+ (((float)b - 45261.36)/7281.40957167)*(-0.448293161912) 
		+ (((float)c - 133028.24)/16919.8930523)*(-1.13028323825);
    }

float check_if_it_is_yellow_object(float r, float g, float b, float c)
    {
        return -2.34841520404 + (((float)r - 48569.2)/10044.1032731)*(0.188194428582) 
		+ (((float)g - 38272.4)/5813.49153607)*(2.01927024535) 
		+ (((float)b - 45261.36)/7281.40957167)*(-0.140629957025) 
		+ (((float)c - 133028.24)/16919.8930523)*(0.812612435966);
    }

int make_a_decision(float r, float g, float b, float c)
    {
        int max_id = 0;
        float max_value = -10000;
        float value;
        value = check_if_it_is_blue_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 0;
            max_value = value;
        }
    
        value = check_if_it_is_green_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 1;
            max_value = value;
        }
    
        value = check_if_it_is_orange_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 2;
            max_value = value;
        }
    
        value = check_if_it_is_red_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 3;
            max_value = value;
        }
    
        value = check_if_it_is_white_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 4;
            max_value = value;
        }
    
        value = check_if_it_is_yellow_object(r, g, b, c);
        if (value > max_value)
        {
            max_id = 5;
            max_value = value;
        }
    
        return max_id;
    }
    