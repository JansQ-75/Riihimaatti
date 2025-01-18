const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
  console.log(req.headers);
  const authHeader = req.headers.authorization;

  if (!authHeader) return res.sendStatus(401);

  jwt.verify(authHeader, process.env.JWT_TOKEN, function (err, user) {
    if (err) return res.sendStatus(403);

    req.user = user;

    next();
  });
}

module.exports = authenticateToken;
