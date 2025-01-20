const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
  const authHeader = req.headers.authorization;
  const token = authHeader && authHeader.split(' ')[1];
  if (!token) return res.sendStatus(401);

  jwt.verify(authHeader, process.env.JWT_TOKEN, function (err, cardnumber) {
    if (err) return res.sendStatus(403);

    req.cardnumber = cardnumber;

    next();
  });
}

module.exports = authenticateToken;
