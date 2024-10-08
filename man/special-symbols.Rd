\name{special-symbols}
\alias{special-symbols}
\alias{datatable-symbols}
\alias{.SD}
\alias{.I}
\alias{.GRP}
\alias{.BY}
\alias{.N}
\alias{.EACHI}
\alias{.NGRP}
\alias{.NATURAL}
\title{ Special symbols }
\description{
    \code{.SD}, \code{.BY}, \code{.N}, \code{.I}, \code{.GRP}, and \code{.NGRP} are \emph{read-only} symbols for use in \code{j}. \code{.N} can be used in \code{i} as well. \code{.I} can be used in \code{by} as well. See the vignettes, Details and Examples here and in \code{\link{data.table}}.
    \code{.EACHI} is a symbol passed to \code{by}; i.e. \code{by=.EACHI}, \code{.NATURAL} is a symbol passed to \code{on}; i.e. \code{on=.NATURAL}
}
\details{
    The bindings of these variables are locked and attempting to assign to them will generate an error. If you wish to manipulate \code{.SD} before returning it, take a \code{\link{copy}(.SD)} first (see FAQ 4.5). Using \code{:=} in the \code{j} of \code{.SD} is reserved for future use as a (tortuously) flexible way to update \code{DT} by reference by group (even when groups are not contiguous in an ad hoc by).

    These symbols used in \code{j} are defined as follows.

    \itemize{
        \item \code{.SD} is a \code{data.table} containing the \bold{S}ubset of \code{x}'s \bold{D}ata for each group, excluding any columns used in \code{by} (or \code{keyby}).
        \item \code{.BY} is a \code{list} containing a length 1 vector for each item in \code{by}. This can be useful when \code{by} is not known in advance. The \code{by} variables are also available to \code{j} directly by name; useful for example for titles of graphs if \code{j} is a plot command, or to branch with \code{if()} depending on the value of a group variable.
        \item \code{.N} is an integer, length 1, containing the number of rows in the group. This may be useful when the column names are not known in advance and for convenience generally. When grouping by \code{i}, \code{.N} is the number of rows in \code{x} matched to, for each row of \code{i}, regardless of whether \code{nomatch} is \code{NA} or \code{NULL}. It is renamed to \code{N} (no dot) in the result (otherwise a column called \code{".N"} could conflict with the \code{.N} variable, see FAQ 4.6 for more details and example), unless it is explicitly named; e.g., \code{DT[,list(total=.N),by=a]}.
        \item \code{.I} is an integer vector equal to \code{seq_len(nrow(x))}. While grouping, it holds for each item in the group, its row location in \code{x}. This is useful to subset in \code{j}; e.g. \code{DT[, .I[which.max(somecol)], by=grp]}. If used in \code{by} it corresponds to applying a function rowwise. 
        \item \code{.GRP} is an integer, length 1, containing a simple group counter. 1 for the 1st group, 2 for the 2nd, etc.
        \item \code{.NGRP} is an integer, length 1, containing the number of groups. 
    }

    \code{.EACHI} is defined as \code{NULL} but its value is not used. Its usage is \code{by=.EACHI} (or \code{keyby=.EACHI}) which invokes grouping-by-each-row-of-i; see \code{\link{data.table}}'s \code{by} argument for more details.

    \code{.NATURAL} is defined as \code{NULL} but its value is not used. Its usage is \code{on=.NATURAL} (alternative of \code{X[on=Y]}) which joins two tables on their common column names, performing a natural join; see \code{\link{data.table}}'s \code{on} argument for more details.

    Note that \code{.N} in \code{i} is computed up-front, while that in \code{j} applies \emph{after filtering in \code{i}}. That means that even absent grouping, \code{.N} in \code{i} can be different from \code{.N} in \code{j}. See Examples.

    Note also that you should consider these symbols read-only and of limited scope -- internal data.table code might manipulate them in unexpected ways, and as such their bindings are locked. There are subtle ways to wind up with the wrong object, especially when attempting to copy their values outside a grouping context. See examples; when in doubt, \code{copy()} is your friend.
}
\seealso{
    \code{\link{data.table}}, \code{\link{:=}}, \code{\link{set}}, \code{\link{datatable-optimize}}
}
\examples{
DT = data.table(x=rep(c("b","a","c"),each=3), v=c(1,1,1,2,2,1,1,2,2), y=c(1,3,6), a=1:9, b=9:1)
DT
X = data.table(x=c("c","b"), v=8:7, foo=c(4,2))
X

DT[.N]                                 # last row, only special symbol allowed in 'i'
DT[, .N]                               # total number of rows in DT
DT[, .N, by=x]                         # number of rows in each group
DT[, .SD, .SDcols=x:y]                 # select columns 'x' through 'y'
DT[, .SD[1]]                           # first row of all columns
DT[, .SD[1], by=x]                     # first row of all columns for each group in 'x'
DT[, c(.N, lapply(.SD, sum)), by=x]    # get rows *and* sum all columns by group
DT[, .I[1], by=x]                      # row number in DT corresponding to each group
DT[, .N, by=rleid(v)]                  # get count of consecutive runs of 'v'
DT[, c(.(y=max(y)), lapply(.SD, min)),
        by=rleid(v), .SDcols=v:b]      # compute 'j' for each consecutive runs of 'v'
DT[, grp := .GRP, by=x]                # add a group counter
DT[, grp_pct := .GRP/.NGRP, by=x]      # add a group "progress" counter
X[, DT[.BY, y, on="x"], by=x]          # join within each group
DT[X, on=.NATURAL]                     # join X and DT on common column similar to X[on=Y]

# .N can be different in i and j
DT[{cat(sprintf('in i, .N is \%d\n', .N)); a < .N/2},
   {cat(sprintf('in j, .N is \%d\n', .N)); mean(a)}]

# .I can be different in j and by, enabling rowwise operations in by
DT[, .(.I, min(.SD[,-1]))]
DT[, .(min(.SD[,-1])), by=.I]

# Do not expect this to correctly append the value of .BY in each group; copy(.BY) will work.
by_tracker = list()
DT[, { append(by_tracker, .BY); sum(v) }, by=x]
}
\keyword{ data }
