static void
nbstack(Monitor *m) {
	int x, y, h, w, mh, nmax, nm;
	unsigned int i, n;
	Client *c;

	snprintf(m->ltsymbol, sizeof m->ltsymbol, "T%dT", m->nmasters[m->curtag]);
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	c = nexttiled(m->clients);
	nmax = m->nmasters[m->curtag];
	nm = nmax == 1 ? 1 : MIN(n / 2, nmax);
	if(nm > n)
		nm = n;
	/* master */
	if(nm > 0) {
		mh = m->mfacts[m->curtag] * m->wh;
		w = m->ww / nm;
		if(w < bh)
			w = m->ww;
		x = m->wx;
		for(i = 0; i < nm; i++, c = nexttiled(c->next)) {
			resize(c, x, m->wy, ((i + 1 == nm) ? m->wx + m->ww - x : w) - 2 * c->bw,
			       (n == nm ? m->wh : mh) - 2 * c->bw, False);
			if(w != m->ww)
				x = c->x + WIDTH(c);
		}
		n -= nm;
	} else
		mh = 0;
	if(n == 0)
		return;
	/* tile stack */
	x = m->wx;
	y = m->wy + mh;
	w = m->ww / n;
	h = m->wh - mh;
	if(w < bh)
		w = m->ww;
	for(i = 0; c; c = nexttiled(c->next), i++) {
		resize(c, x, y, ((i + 1 == n) ? m->wx + m->ww - x : w) - 2 * c->bw,
		       h - 2 * c->bw, False);
		if(w != m->ww)
			x = c->x + WIDTH(c);
	}
}
