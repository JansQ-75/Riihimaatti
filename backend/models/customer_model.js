const db = require('../database');

const customer = {
    //Get all customer data
    getAll: function(callback) {
        return db.query('SELECT * FROM customer;', callback);
    },
    //Get custormer by id
    getById:function(idcustomer, callback){
        return db.query('SELECT * FROM customer WHERE idcustomer=?',[idcustomer],callback);
    },
    //Add a customer
    add:function(customer_data, callback){
        return db.query('INSERT INTO customer(fname, lname, address, phone) VALUES(?,?,?,?)',[customer_data.fname,customer_data.lname,customer_data.address, customer_data.phone], callback);
    },
    //Update a customer
    update:function(idcustomer,customer_data, callback){
        return db.query('UPDATE customer SET fname=?, lname=?, address=?, phone=? WHERE idcustomer=?',[customer_data.fname,customer_data.lname,customer_data.address, customer_data.phone, idcustomer],callback);
    },
    //Remove a customer
    delete:function(id, callback){
        return db.query('DELETE FROM customer WHERE idcustomer=?',[id], callback);
    },
}

module.exports = customer;