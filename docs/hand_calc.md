$$
\begin{align*}
\mathbf{x}_0^{[0]} &= \begin{bmatrix} 0 \\ 0 \\ 0 \end{bmatrix} &
\mathbf{v}_0^{[0]} &= \begin{bmatrix} -1 \\ 0 \\ 0 \end{bmatrix} \\
\mathbf{x}_1^{[0]} &= \begin{bmatrix} 0 \\ 2 \\ 0 \end{bmatrix} &
\mathbf{v}_1^{[0]} &= \begin{bmatrix} 1 \\ 0 \\ 0 \end{bmatrix}
\end{align*}\\

m_0 = m_1 = 10, \qquad L = 1, \qquad k = 40, \qquad \Delta t = 0.1\\

\textbf{Spring force:}
\begin{align*}
\mathbf{d} &= \mathbf{x}_1 - \mathbf{x}_0, \qquad l = \|\mathbf{d}\|, \qquad \hat{\mathbf{d}} = \mathbf{d}/l \\
\mathbf{F}_0 &= \underline{\hspace{1cm}}\, k\,(l - L)\,\hat{\mathbf{d}}, \qquad
\mathbf{F}_1 = -\mathbf{F}_0 \\
\mathbf{a}_i &= \mathbf{F}_i / m_i
\end{align*} \\

\textbf{Euler:}\\
\begin{align*}
\mathbf{x}_i^{[1]} &= \mathbf{x}_i^{[0]} + \Delta t\,\mathbf{v}_i^{[0]} \\
\mathbf{v}_i^{[1]} &= \mathbf{v}_i^{[0]} + \Delta t\,\mathbf{a}_i^{[0]}
\end{align*} \\

\textbf{Midpoint:}
\begin{align*}
\end{align*}
$$
