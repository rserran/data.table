\name{subset.data.table}
\alias{subset}
\alias{subset.data.table}

\title{ Subsetting data.tables }

\description{
  Returns subsets of a \code{data.table}.
}

\usage{
  \method{subset}{data.table}(x, subset, select, ...)
}

\arguments{
  \item{x}{
    \code{data.table} to subset.
  }
  \item{subset}{
    logical expression indicating elements or rows to keep
  }
  \item{select}{
    expression indicating columns to select from \code{data.table}
  }
  \item{\ldots}{
    further arguments to be passed to or from other methods
  }
}

\details{
  The \code{subset} argument works on the rows and will be evaluated
  in the \code{data.table} so columns can be referred to (by name) as variables
  in the expression.

  The \code{data.table} that is returned will maintain the original keys
  as long as they are not \code{select}-ed out.
}

\value{
  A \code{data.table} containing the subset of rows and columns that are
  selected.
}
\seealso{ \code{\link[base]{subset}} }
\examples{

DT <- data.table(a=sample(c('a', 'b', 'c'), 20, replace=TRUE),
                 b=sample(c('a', 'b', 'c'), 20, replace=TRUE),
                 c=sample(20), key=c('a', 'b'))

sub <- subset(DT, a == 'a')
all.equal(key(sub), key(DT))
}
\keyword{ data }


