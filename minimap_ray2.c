dof = 0;  //check vertical line
		float nTan;
		float disV=1000000;
		float vx, vy;
		if (ra > M_PI * 0.5 - 0.00001 && ra < M_PI * 0.5)
			nTan = 2147483647;
		else if (ra < M_PI * 0.5 + 0.00001 && ra > M_PI * 0.5)
			nTan = -2147483647;
		else if (ra > M_PI * 1.5 - 0.00001 && ra < M_PI * 1.5)
			nTan = 2147483647;
		else if (ra < M_PI * 1.5 + 0.00001 && ra > M_PI * 1.5)
			nTan = -2147483647;	
		else
			nTan = -tan(ra);

		//float nTan = -tan(ra);
		if (ra == 0  || ra == M_PI) //player schaut oben unten
		{
			rx = arr->p_x; ry=arr->p_y; dof = arr->dof;
		}
		else if (ra < M_PI * 0.5 || ra > M_PI * 1.5)//player schaut nach links??
		{
			rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) - 0.0001;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = - arr->subsize;
			yo = -xo * nTan *1;
			direction = direction + 30;

	//printf("schaut nach links\n");
	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		else if (ra > M_PI * 0.5 && ra < M_PI * 1.5)//player schaut nach rechts??
		{
			rx = (((int)arr->p_x >> arr->sub_bit) << arr->sub_bit) + arr->subsize;
			ry = (arr->p_x - rx) * nTan + arr->p_y;
			xo = arr->subsize;
			yo = -xo * nTan;
			direction = direction + 10;

	//printf("schaut nach rechts\n");

	 //printf("ra: %f rx: %f ry: %f\n",ra, rx, ry);
	 //printf("yo: %f xo: %f nTan: %f\n",yo, xo, nTan);
		}
		while (dof < arr->dof)
		{
			//printf("mx: %d my: %d mp: %d\n",mx, my, mp);
			mx = (int) (rx) >> arr->sub_bit;
			my = (int) (ry) >> arr->sub_bit;
			mp = my * arr->cols + mx;
			//printf("map: %c my:%d mx:%d\n",arr->map[mp], my, mx);

			if (mp >= 0 && mp < arr->cols * arr->rows && arr->map[mp] == '1')
			{
				vx = rx; vy=ry; disV=dist_vec(arr,rx,ry);
				dof = arr->dof;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}