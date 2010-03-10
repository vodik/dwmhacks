static void
setopy(const Arg *arg) {
	Client *c = selmon->sel;

	if(c->opacity == -1 && arg->i < 0)
		c->opacity = 100 + arg->i;
	else if(c->opacity == -1 && arg->i > 0)
		return;
	else {
		c->opacity += arg->i;

		if(c->opacity >= 100)
			c->opacity = -1;
		else if(c->opacity < 0)
			c->opacity = 0;
	}

	opacify(c, c->opacity);
}
