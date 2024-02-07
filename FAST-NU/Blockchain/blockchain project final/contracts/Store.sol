pragma solidity 0.5.16;

import "./Escrow.sol";

contract Store {
    enum ProductStatus { Available, Processing, Shipping, Sold }

    struct Product {
        string name;
        string category;
        string imageLink;
        string descLink;
        uint price;
        uint index;
        ProductStatus status;
    }

    struct Order {
        bytes32 productId;
        address seller;
        address buyer;
        address escrow;
    }

    address owner;
    mapping(bytes32 => Product) products;
    mapping(bytes32 => Order) orders;
    bytes32[] productIds;

    event ProductCreated(
        bytes32 indexed id,
        uint index,
        string name,
        string category,
        string imageLink,
        string descLink,
        uint price,
        ProductStatus status
    );

    event ProductUpdated(
        bytes32 indexed id,
        uint index,
        string name,
        string category,
        string imageLink,
        string descLink,
        uint price,
        ProductStatus status
    );

    event OrderCreated(
        bytes32 indexed productId,
        address indexed seller,
        address indexed buyer,
        address escrow
    );

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }

    constructor () public {
        owner = msg.sender;
    }

    function addProduct(
        string memory name,
        string memory category,
        string memory imageLink,
        string memory descLink,
        uint price
    )
        public onlyOwner returns (uint)
    {
        bytes32 id = keccak256(abi.encode(name, category, imageLink, descLink, price));

        require(!isProduct(id));

        products[id].name = name;
        products[id].category = category;
        products[id].imageLink = imageLink;
        products[id].descLink = descLink;
        products[id].price = price;
        products[id].index = productIds.push(id) - 1;
        products[id].status = ProductStatus.Available;

        emit ProductCreated(
            id,
            products[id].index,
            name,
            category,
            imageLink,
            descLink,
            price,
            ProductStatus.Available
        );

        return products[id].index;
    }

    function placeOrder(bytes32 id) public payable {
        require(isProduct(id));
        require(msg.value >= products[id].price);
        require(products[id].status == ProductStatus.Available);
        address seller = owner; // Only allow owner sell items for now
        address buyer = msg.sender;
        address escrow = address((new Escrow).value(msg.value)(buyer, seller, id));

        orders[id].productId = id;
        orders[id].seller = seller;
        orders[id].buyer = buyer;
        orders[id].escrow = escrow;

        updateProductStatus(id, ProductStatus.Processing);

        emit OrderCreated(id, seller, buyer, escrow);
    }

    function isProduct(bytes32 id) public view returns (bool) {
        if (productIds.length == 0) {
            return false;
        }

        return productIds[products[id].index] == id;
    }

    function getProduct(bytes32 id)
        public
        view
        returns (
            string memory,
            string memory,
            string memory,
            string memory,
            uint,
            uint,
            ProductStatus
        )
    {
        require(isProduct(id));

        return (
            products[id].name,
            products[id].category,
            products[id].imageLink,
            products[id].descLink,
            products[id].price,
            products[id].index,
            products[id].status
        );
    }

    function getProductCount() public view returns (uint) {
        return productIds.length;
    }

    function getProductIdAt(uint index) public view returns (bytes32) {
        return productIds[index];
    }

    function updateProductStatus(bytes32 id, ProductStatus status)
        public returns (bool)
    {
        require(isProduct(id));

        products[id].status = status;

        emit ProductUpdated(
            id,
            products[id].index,
            products[id].name,
            products[id].category,
            products[id].imageLink,
            products[id].descLink,
            products[id].price,
            status
        );

        return true;
    }
}
